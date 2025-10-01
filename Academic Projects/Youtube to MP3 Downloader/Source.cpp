#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <sstream>

//Note to self--turns out it isn't that hard to find the proper URL for most videos, I've already done it.
//The hard part is encryption.  Youtube has some encrypted videos; vlc media player can deal with this, I can't.
//https://www.quora.com/How-can-I-make-a-YouTube-video-downloader-web-application-from-scratch this forum might have some helpful information, should I decide to try my hand at decryption.

using namespace std;

string bitrate; //the bitrate to save MP3 files with
string OutputPath; //the path to the folder where output files will be stored, NOT the files themselves (including trailing \)
string VLCPath; //the path to the folder that contains vlc.exe, NOT vlc.exe itself (including trailing \)
string FFMPEGPath; //the path to the folder that contains ffmpeg.exe, NOT ffmpeg.exe itself (including trailing \)

string IsolateStringIntervals(string contents, string first, string last) { //returns a substring containing all the URL values (surrounded by lots of other information), and ending with the number of total videos
	size_t start = contents.find(first); //string that shows up first before the first **important** instance of "/watch?v=":
	size_t end = contents.rfind(last); //string that shows up first after the last **important** "/watch?v=":
	if (start == string::npos || end == string::npos) return "ERROR";
	return contents.substr(start, (end - start));
}

bool StringVectorContains(const vector<string> v, string addition) {
	int j = v.size();
	for (int i = 0; i < j; i++) {
		if (v[i] == addition) return true;
	}
	return false;
}

void ParseYoutubePlaylistListFromHTML(string input, vector<string>& urls) { //arguments: string of raw HTML dump from youtube playlist first video; returns a vector of strings containing the video URLs for all videos contained in a playlist, as of youtube's format on Nov. 8 2017
	string contents = IsolateStringIntervals(input, "playlist-videos-container", "playlist-video-description");
	vector<string> returnvector;
	if (contents == "ERROR") {
		urls = returnvector;
		return;
	}
	string headString("/watch?v="); //the string that shows up before what comes after the watch?v= youtube URL section

	size_t position = contents.find(headString);
	size_t end = contents.rfind(headString);
	size_t urllen;

	while (position < end) {
		string addition;

		position = contents.find(headString, position);
		position = position + 9; //9 is the amount of characters from the first /watch?v= to the first significant character in the URL information
		urllen = contents.find("&", position); //find the ampersand that comes at the end of the URL data

		addition = contents.substr(position, urllen - position);
		if (!StringVectorContains(returnvector, addition)) returnvector.push_back(addition);
	}

	int j = returnvector.size();
	for (int i = 0; i < j; i++) {
		returnvector[i] = "https://www.youtube.com/watch?v=" + returnvector[i]; //the first section of URL
	}

	urls = returnvector;
	return;
}

bool CheckPlaylistURL(string input) { //checks to see if the URL is a playlist or not
	if (input.find("list") == string::npos) return false; //"list" shows up in playlist URLs
	return true;
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{ //some sort of curl magic
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

void SetOptions(ifstream* options) { //sets the global path options based on the input from options.txt
	getline(*options, bitrate);
	getline(*options, bitrate);
	
	getline(*options, OutputPath);
	getline(*options, OutputPath);

	getline(*options, VLCPath);
	getline(*options, VLCPath);

	getline(*options, FFMPEGPath);
	getline(*options, FFMPEGPath);

	return;
}

string CreateVLCCommand(string URL, int i) { //creates an individual VLC command line call based on the options set and URLs saved
	stringstream ss;
	ss << i;
	string Command("\"" + VLCPath + "vlc\" " + URL + " --no-loop --play-and-exit --no-crashdump --sout=#file{dst=\"" + OutputPath + ss.str() + ".mp4\"}\n");
	return Command;
}

string CreateFFMPEGCommand(int i) { //creates an individual FFMPEG command line call based on the options set
	stringstream ss;
	ss << i;
	string Command("\"" + FFMPEGPath + "ffmpeg\" -i \"" + OutputPath + ss.str() + ".mp4\" -b:a " + bitrate + "k \"" + OutputPath + ss.str() + ".mp3\"\n");
	return Command;
}

string CreateDelCommand(int i) { //creates an individual del command line call based on the options set
	stringstream ss;
	ss << i;
	string Command("del \"" + OutputPath + ss.str() + ".mp4\"\n");
	return Command;
}

void CreateBatchFile(const vector<string>* urls) { //creates the batch file windows will call
	string command;
	string contents;
	ofstream batch;
	int j = urls->size();

	for (int i = 0; i < j; i++) {
		command = CreateVLCCommand(urls->at(i), i + 1);
		contents += command;

		command = CreateFFMPEGCommand(i + 1);
		contents += command;

		command = CreateDelCommand(i + 1);
		contents += command;
	}

	batch.open("temp.bat");
	batch.write(&contents.at(0), contents.size());

	return;
}

string ReturnHTMLDump(string url) {
	CURL *curl;
	CURLcode res;
	string html;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);
		res = curl_easy_perform(curl);

		curl_easy_cleanup(curl);
	}

	return html;
}

void ReplaceSubstring(string& content, string find, string replacement) {
	size_t start;

	while (1) {
		start = content.find(find);
		if (start == string::npos) break;
		content.replace(start, find.size(), replacement);
	}
	
	return;
}

string ParseHTMLDumpForNewURL(string html) {
	string url;
	size_t start = 0;
	size_t end;
	size_t endtest;
	vector<string> possibles;

	while (1) {
		start = html.find("mime%3Daudio%252F", start);
		if (start == string::npos) break;
		start = html.rfind("https", start);
		end = html.find("\\", start);
		endtest = html.find(",", start);
		if (endtest < end) end = endtest;
		url = html.substr(start, end - start);
		//if (url.find("signature%3D") != string::npos) {
		//if (url.find("ratebypass%3D") != string::npos) {
			ReplaceSubstring(url, "%3A", ":");
			ReplaceSubstring(url, "%2F", "/");
			ReplaceSubstring(url, "%3F", "?");
			ReplaceSubstring(url, "%3D", "=");
			ReplaceSubstring(url, "%26", "&");
			ReplaceSubstring(url, "%25", "%");
			possibles.push_back(url);
			//break;
		//}
			//}
		//}
		start = end;
	}

	ofstream out;
	out.open("Temp.txt");
	for (int i = 0; i < possibles.size(); i++) {
		out.write(&possibles[i].at(0), possibles[i].size());
		out.write("\n", 1);
	}

	//url = html.substr(start, end - start);

	//cout << endl << url << endl;
	//Find first instance of mime%3Dvideo; backwards from there, find first instance of https; truncate from there to next \; then perform above replacements
	//the following fixes html encoding; after this, the url should be the youtube video needed
	/*
	ReplaceSubstring(url, "%3A", ":");
	ReplaceSubstring(url, "%2F", "/");
	ReplaceSubstring(url, "%3F", "?");
	ReplaceSubstring(url, "%3D", "=");
	ReplaceSubstring(url, "%26", "&");
	ReplaceSubstring(url, "%25", "%");
	*/

	//cout << endl << url << endl;

	return url;
}

int main() {
	string html;
	string url;
	string input;
	ifstream options;
	vector<string> urls;

	cout << "Enter video/playlist URL (must be a youtube watch?v= page): ";
	getline(cin, input);
	cout << "\n";

	if (input.substr(0, 32) != "https://www.youtube.com/watch?v=") {
		cout << "USER ERROR - Invalid URL\n";
		return 1;
	}

	if (!CheckPlaylistURL(input)) urls.push_back(input);
	else {
		cout << "Fetching information for playlist...\n";
		html = ReturnHTMLDump(input);
		if (html == "") {
			cout << "CURL ERROR - Empty source code\n";
			return 2;
		}

		ParseYoutubePlaylistListFromHTML(html, urls);

		if (urls.size() == 0) {
			cout << "YOUTUBE/CURL ERROR - Source code returned no URLs\n";
			return 3;
		}
	}

	//for loop call to function that uses CURL to download new URL html, then parses it, and replaces the URL with the parsed string
	int j = urls.size();
	for (int i = 0; i < j; i++) {
		cout << "Fetching information for video " << to_string(i + 1) << "...\n";
		html = ReturnHTMLDump(urls[i]);
		url = ParseHTMLDumpForNewURL(html);
		urls[i] = url;
	}

	cout << "Opening options.txt...\n";
	options.open("options.txt");
	if (!options.is_open()) {
		cout << "USER ERROR - options.txt not found\n";
		return 4;
	}

	SetOptions(&options);

	CreateBatchFile(&urls);

	system("temp.bat");
	system("del temp.bat");

	cout << "\nDone!\n";

	return 0;
}

//%3A	:
//%2F	/
//%3F	?
//%3D	=
//%25	%
//%26	&
/*

https://r3---sn-bvvbax4pcxg-naje.googlevideo.com/videoplayback?
source=youtube&
lmt=1503673707555684&
ei=KBwGWqyLLIjjuQWMoIWIAg&
mt=1510349705&
mv=m&
sparams=dur%2Cei%2Cgcr%2Cid%2Cinitcwndbps%2Cip%2Cipbits%2Citag%2Clmt%2Cmime%2Cmm%2Cmn%2Cms%2Cmv%2Cpl%2Cratebypass%2Crequiressl%2Csource%2Cexpire&
ms=au&
ip=2605%3Aa601%3A504%3Aa901%3Aa863%3A87ea%3A7f24%3Af362&
requiressl=yes&
mm=31&
mn=sn-bvvbax4pcxg-naje&
id=o-ADBMfkDtROxwAt7CfZPAqxNa27fup16Y2tcyxPvvQ2xS&
pl=44&
gcr=us&
itag=22&
initcwndbps=1677500&
ratebypass=yes&
expire=1510371464&
ipbits=0&
dur=113.940&
mime=video%2Fmp4&
key=yt6&
signature=AD751DF299C9153E40D3B1423AAC192E96282CF1.75080DD489D0569282646F5D8515336403B268AB


initcwndbps=1753750&ratebypass=yes&expire=1510373511&ipbits=0&dur=113.940&mime=video%2Fmp4&key=yt6&signature=1719829AB2C96E608668771444C70272E0F0C7DF.1EBADCAD02C4248ACF5C5F83777ACA149EE9DCF7*/