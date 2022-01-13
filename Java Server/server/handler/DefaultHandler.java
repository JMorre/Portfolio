package server.handler;

import java.io.File;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

public class DefaultHandler extends Handler implements HttpHandler {

	@Override
	public void handle(HttpExchange exchange) throws IOException { //can i check if its asking for files or handle?

		Path path = getURIPath(exchange);
		if (path.equals(Paths.get("/"))) {
			path = Paths.get("index.html");
		}
		
		path = Paths.get("web", path.toString());
		
		File f = path.toFile();
		if (!f.isFile()) {
			path = Paths.get("web", "HTML", "404.html");
			f = path.toFile();
		}
		
		OutputStream os = exchange.getResponseBody();
		exchange.sendResponseHeaders(200, f.length());
		Files.copy(path, os);
		os.close();
		
	}
}
