#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <ctype.h>
#include <vector>

int FourLittleByteStringToInteger(std::string s) {
	if (s.size() != 4) return 0;

	int i = (int)((unsigned char)(s[0]) | (unsigned char)(s[1]) << 8 | (unsigned char)(s[2]) << 16 | (unsigned char)(s[3]) << 24);
	return i;
}

long EightLittleByteStringToInteger(std::string s) {
	if (s.size() != 8) return 0;

	int i = (int)((unsigned char)(s[0]) | (unsigned char)(s[1]) << 8 | (unsigned char)(s[2]) << 16 | (unsigned char)(s[3]) << 24 | (unsigned char)(s[4]) << 32 | (unsigned char)(s[5]) << 40 | (unsigned char)(s[6]) << 48 | (unsigned char)(s[7]) << 56);
	return i;
}

std::string UnitType(long ID, std::string PlayerName) {
	switch (ID) {
	case -1: return "Nobody";
	case 0: return PlayerName;
	case 1: return "Multiplayer Male";
	case 2: return "Multiplayer Female";
	case 3: return "Temp Troop";
	case 4: return "Find Item Cheat";
	case 5: return "Random Town Sequence";
	case 6: return "Tournament Participant";
	case 7: return "Maceman";
	case 8: return "Archer";
	case 9: return "Swordsman";
	case 10: return "Novice Fighter";
	case 11: return "Regular Fighter";
	case 12: return "Veteran Fighter";
	case 13: return "Champion Fighter";
	case 14: return "Novice Fighter";
	case 15: return "Novice Fighter";
	case 16: return "Regular Fighter";
	case 17: return "Regular Fighter";
	case 18: return "Regular Fighter";
	case 19: return "Veteran Fighter";
	case 20: return "Veteran Fighter";
	case 21: return "Veteran Fighter";
	case 22: return "Champion Fighter";
	case 23: return "Champion Fighter";
	case 24: return "Cattle";
	case 25: return "Farmer";
	case 26: return "Townsman";
	case 27: return "Watchman";
	case 28: return "Caravan Guard";
	case 29: return "Mercenary Swordsman";
	case 30: return "Hired Blade";
	case 31: return "Mercenary Crossbowman";
	case 32: return "Mercenary Horseman";
	case 33: return "Mercenary Cavalry";
	case 34: return "Mercenaries End";
	case 35: return "Swadian Recruit";
	case 36: return "Swadian Militia";
	case 37: return "Swadian Footman";
	case 38: return "Swadian Infantry";
	case 39: return "Swadian Sergeant";
	case 40: return "Swadian Skirmisher";
	case 41: return "Swadian Crossbowman";
	case 42: return "Swadian Sharpshooter";
	case 43: return "Swadian Man at Arms";
	case 44: return "Swadian Knight";
	case 45: return "Swadian Messenger";
	case 46: return "Swadian Deserter";
	case 47: return "Prison Guard";
	case 48: return "Castle Guard";
	case 49: return "Vaegir Recruit";
	case 50: return "Vaegir Footman";
	case 51: return "Vaegir Skirmisher";
	case 52: return "Vaegir Archer";
	case 53: return "Vaegir Marksman";
	case 54: return "Vaegir Veteran";
	case 55: return "Vaegir Infantry";
	case 56: return "Vaegir Guard";
	case 57: return "Vaegir Horseman";
	case 58: return "Vaegir Knight";
	case 59: return "Vaegir Messenger";
	case 60: return "Vaegir Deserter";
	case 61: return "Prison Guard";
	case 62: return "Castle Guard";
	case 63: return "Khergit Tribesman";
	case 64: return "Khergit Skirmisher";
	case 65: return "Khergit Horseman";
	case 66: return "Khergit Horse Archer";
	case 67: return "Khergit Veteran Horse Archer";
	case 68: return "Khergit Lancer";
	case 69: return "Khergit Messenger";
	case 70: return "Khergit Deserter";
	case 71: return "Prison Guard";
	case 72: return "Castle Guard";
	case 73: return "Nord Recruit";
	case 74: return "Nord Footman";
	case 75: return "Nord Trained Footman";
	case 76: return "Nord Warrior";
	case 77: return "Nord Veteran";
	case 78: return "Nord Huscarl";
	case 79: return "Nord Huntsman";
	case 80: return "Nord Archer";
	case 81: return "Nord Veteran Archer";
	case 82: return "Nord Messenger";
	case 83: return "Nord Deserter";
	case 84: return "Prison Guard";
	case 85: return "Castle Guard";
	case 86: return "Rhodok Tribesman";
	case 87: return "Rhodok Spearman";
	case 88: return "Rhodok Trained Spearman";
	case 89: return "Rhodok Veteran Spearman";
	case 90: return "Rhodok Sergeant";
	case 91: return "Rhodok Crossbowman";
	case 92: return "Rhodok Trained Crossbowman";
	case 93: return "Rhodok Veteran Crossbowman";
	case 94: return "Rhodok Sharpshooter";
	case 95: return "Rhodok Messenger";
	case 96: return "Rhodok Deserter";
	case 97: return "Prison Guard";
	case 98: return "Castle Guard";
	case 99: return "Sarranid Recruit";
	case 100: return "Sarranid Footman";
	case 101: return "Sarranid Veteran Footman";
	case 102: return "Sarranid Infantry";
	case 103: return "Sarranid Guard";
	case 104: return "Sarranid Skirmisher";
	case 105: return "Sarranid Archer";
	case 106: return "Sarranid Master Archer";
	case 107: return "Sarranid Horseman";
	case 108: return "Sarranid Mamluke";
	case 109: return "Sarranid Messenger";
	case 110: return "Sarranid Deserter";
	case 111: return "Prison Guard";
	case 112: return "Castle Guard";
	case 113: return "Looter";
	case 114: return "Bandit";
	case 115: return "Brigand";
	case 116: return "Mountain Bandit";
	case 117: return "Forest Bandit";
	case 118: return "Sea Raider";
	case 119: return "Steppe Bandit";
	case 120: return "Taiga Bandit";
	case 121: return "Desert Bandit";
	case 122: return "Black Khergit Horseman";
	case 123: return "Manhunter";
	case 124: return "Slave Driver";
	case 125: return "Slave Hunter";
	case 126: return "Slave Crusher";
	case 127: return "Slaver Chief";
	case 128: return "Camp Follower";
	case 129: return "Huntress";
	case 130: return "Camp Defender";
	case 131: return "Sword Sister";
	case 132: return "Refugee";
	case 133: return "Peasant Woman";
	case 134: return "Caravan Master";
	case 135: return "Kidnapped Girl";
	case 136: return "Townsman";
	case 137: return "Townswoman";
	case 138: return "Townsman";
	case 139: return "Townswoman";
	case 140: return "Townsman";
	case 141: return "Townswoman";
	case 142: return "Villager";
	case 143: return "Villager";
	case 144: return "Townsman";
	case 145: return "Townswoman";
	case 146: return "Tournament Master";
	case 147: return "Trainer";
	case 148: return "Constable Hareck";
	case 149: return "Ramun, the Slave Trader";
	case 150: return "Quick Jimmy";
	case 151: return "Xerina";
	case 152: return "Dranton";
	case 153: return "Kradus";
	case 154: return "Training Ground Master";
	case 155: return "Tutorial Student 1";
	case 156: return "Tutorial Student 2";
	case 157: return "Tutorial Student 3";
	case 158: return "Tutorial Student 4";
	case 159: return "Galeas";
	case 160: return "Farmer";
	case 161: return "Trainer";
	case 162: return "Trainer";
	case 163: return "Trainer";
	case 164: return "Trainer";
	case 165: return "Trainer";
	case 166: return "Ransom Broker";
	case 167: return "Ransom Broker";
	case 168: return "Ransom Broker";
	case 169: return "Ransom Broker";
	case 170: return "Ransom Broker";
	case 171: return "Ransom Broker";
	case 172: return "Ransom Broker";
	case 173: return "Ransom Broker";
	case 174: return "Ransom Broker";
	case 175: return "Ransom Broker";
	case 176: return "Traveller";
	case 177: return "Traveller";
	case 178: return "Traveller";
	case 179: return "Traveller";
	case 180: return "Traveller";
	case 181: return "Traveller";
	case 182: return "Traveller";
	case 183: return "Traveller";
	case 184: return "Traveller";
	case 185: return "Traveller";
	case 186: return "Book Merchant";
	case 187: return "Book Merchant";
	case 188: return "Wandering Minstrel";
	case 189: return "Wandering Bard";
	case 190: return "Wandering Ashik";
	case 191: return "Wandering Skald";
	case 192: return "Wandering Troubadour";
	case 193: return "Kingdom Heroes";
	case 194: return "Borcha";
	case 195: return "Marnid";
	case 196: return "Ymira";
	case 197: return "Rolf";
	case 198: return "Baheshtur";
	case 199: return "Firentis";
	case 200: return "Deshavi";
	case 201: return "Matheld";
	case 202: return "Alayen";
	case 203: return "Bunduk";
	case 204: return "Katrin";
	case 205: return "Jeremus";
	case 206: return "Nizar";
	case 207: return "Lezalit";
	case 208: return "Artimenner";
	case 209: return "Klethi";
	case 210: return "King Harlaus";
	case 211: return "King Yaroglek";
	case 212: return "Sanjar Khan";
	case 213: return "King Ragnar";
	case 214: return "King Graveth";
	case 215: return "Sultan Hakim";
	case 216: return "Count Klargus";
	case 217: return "Count Delinard";
	case 218: return "Count Haringoth";
	case 219: return "Count Clais";
	case 220: return "Count Deglan";
	case 221: return "Count Tredian";
	case 222: return "Count Grainwad";
	case 223: return "Count Ryis";
	case 224: return "Count Plais";
	case 225: return "Count Mirchaud";
	case 226: return "Count Stamar";
	case 227: return "Count Meltor";
	case 228: return "Count Beranz";
	case 229: return "Count Rafard";
	case 230: return "Count Regas";
	case 231: return "Count Devlian";
	case 232: return "Count Rafarch";
	case 233: return "Count Rochabarth";
	case 234: return "Count Despin";
	case 235: return "Count Montewar";
	case 236: return "Boyar Vuldrat";
	case 237: return "Boyar Naldera";
	case 238: return "Boyar Meriga";
	case 239: return "Boyar Khavel";
	case 240: return "Boyar Doru";
	case 241: return "Boyar Belgaru";
	case 242: return "Boyar Ralcha";
	case 243: return "Boyar Vlan";
	case 244: return "Boyar Mleza";
	case 245: return "Boyar Nelag";
	case 246: return "Boyar Crahask";
	case 247: return "Boyar Bracha";
	case 248: return "Boyar Druli";
	case 249: return "Boyar Marmun";
	case 250: return "Boyar Gastya";
	case 251: return "Boyar Harish";
	case 252: return "Boyar Taisa";
	case 253: return "Boyar Valishin";
	case 254: return "Boyar Rudin";
	case 255: return "Boyar Kumipa";
	case 256: return "Alagur Noyan";
	case 257: return "Tonju Noyan";
	case 258: return "Belir Noyan";
	case 259: return "Asugan Noyan";
	case 260: return "Brula Noyan";
	case 261: return "Imirza Noyan";
	case 262: return "Urumuda Noyan";
	case 263: return "Kramuk Noyan";
	case 264: return "Chaurka Noyan";
	case 265: return "Sebula Noyan";
	case 266: return "Tulug Noyan";
	case 267: return "Nasugei Noyan";
	case 268: return "Urubay Noyan";
	case 269: return "Hugu Noyan";
	case 270: return "Tansugai Noyan";
	case 271: return "Tirida Noyan";
	case 272: return "Ulusamai Noyan";
	case 273: return "Karaban Noyan";
	case 274: return "Akadan Noyan";
	case 275: return "Dundush Noyan";
	case 276: return "Jarl Aedin";
	case 277: return "Jarl Irya";
	case 278: return "Jarl Olaf";
	case 279: return "Jarl Reamald";
	case 280: return "Jarl Turya";
	case 281: return "Jarl Gundur";
	case 282: return "Jarl Harald";
	case 283: return "Jarl Knudarr";
	case 284: return "Jarl Haeda";
	case 285: return "Jarl Turegor";
	case 286: return "Jarl Logarson";
	case 287: return "Jarl Aeric";
	case 288: return "Jarl Faarn";
	case 289: return "Jarl Bulba";
	case 290: return "Jarl Rayeck";
	case 291: return "Jarl Dirigun";
	case 292: return "Jarl Marayirr";
	case 293: return "Jarl Gearth";
	case 294: return "Jarl Surdun";
	case 295: return "Jarl Gerlad";
	case 296: return "Count Matheas";
	case 297: return "Count Gutlans";
	case 298: return "Count Laruqen";
	case 299: return "Count Raichs";
	case 300: return "Count Reland";
	case 301: return "Count Tarchias";
	case 302: return "Count Gharmall";
	case 303: return "Count Talbar";
	case 304: return "Count Rimusk";
	case 305: return "Count Falsevor";
	case 306: return "Count Etrosq";
	case 307: return "Count Kurnias";
	case 308: return "Count Tellrog";
	case 309: return "Count Tribidan";
	case 310: return "Count Gerluchs";
	case 311: return "Count Fudreim";
	case 312: return "Count Nealcha";
	case 313: return "Count Fraichin";
	case 314: return "Count Trimbau";
	case 315: return "Count Reichsin";
	case 316: return "Emir Uqais";
	case 317: return "Emir Hamezan";
	case 318: return "Emir Atis";
	case 319: return "Emir Nuwas";
	case 320: return "Emir Mundhalir";
	case 321: return "Emir Ghanawa";
	case 322: return "Emir Nuam";
	case 323: return "Emir Dhiyul";
	case 324: return "Emir Lakhem";
	case 325: return "Emir Ghulassen";
	case 326: return "Emir Azadun";
	case 327: return "Emir Quryas";
	case 328: return "Emir Amdar";
	case 329: return "Emir Hiwan";
	case 330: return "Emir Muhnir";
	case 331: return "Emir Ayyam";
	case 332: return "Emir Raddoun";
	case 333: return "Emir Tilimsan";
	case 334: return "Emir Dhashwal";
	case 335: return "Emir Biliya";
	case 336: return "Lady Isolla of Suno";
	case 337: return "Prince Valdym the Bastard";
	case 338: return "Dustum Khan";
	case 339: return "Lethwin Far-Seeker";
	case 340: return "Lord Kastor of Veluca";
	case 341: return "Arwa the Pearled One";
	case 342: return "Wife Error";
	case 343: return "Lady Anna";
	case 344: return "Lady Nelda";
	case 345: return "Lady Bela";
	case 346: return "Lady Elina";
	case 347: return "Lady Constanis";
	case 348: return "Lady Vera";
	case 349: return "Lady Auberina";
	case 350: return "Lady Tibal";
	case 351: return "Lady Magar";
	case 352: return "Lady Thedosa";
	case 353: return "Lady Melisar";
	case 354: return "Lady Irena";
	case 355: return "Lady Philenna";
	case 356: return "Lady Sonadel";
	case 357: return "Lady Boadila";
	case 358: return "Lady Elys";
	case 359: return "Lady Johana";
	case 360: return "Lady Bernatys";
	case 361: return "Lady Enricata";
	case 362: return "Lady Gaeta";
	case 363: return "Lady Junitha";
	case 364: return "Lady Katia";
	case 365: return "Lady Seomis";
	case 366: return "Lady Drina";
	case 367: return "Lady Nesha";
	case 368: return "Lady Tabath";
	case 369: return "Lady Pelaeka";
	case 370: return "Lady Haris";
	case 371: return "Lady Vayen";
	case 372: return "Lady Joaka";
	case 373: return "Lady Tejina";
	case 374: return "Lady Olekseia";
	case 375: return "Lady Myntha";
	case 376: return "Lady Akilina";
	case 377: return "Lady Sepana";
	case 378: return "Lady Iarina";
	case 379: return "Lady Sihavan";
	case 380: return "Lady Erenchina";
	case 381: return "Lady Tamar";
	case 382: return "Lady Valka";
	case 383: return "Lady Borge";
	case 384: return "Lady Tuan";
	case 385: return "Lady Mahraz";
	case 386: return "Lady Ayasu";
	case 387: return "Lady Ravin";
	case 388: return "Lady Ruha";
	case 389: return "Lady Chedina";
	case 390: return "Lady Kefra";
	case 391: return "Lady Nirvaz";
	case 392: return "Lady Dulua";
	case 393: return "Lady Selik";
	case 394: return "Lady Thalatha";
	case 395: return "Lady Yasreen";
	case 396: return "Lady Nadha";
	case 397: return "Lady Zenur";
	case 398: return "Lady Arjis";
	case 399: return "Lady Atjahan";
	case 400: return "Lady Qutala";
	case 401: return "Lady Hindal";
	case 402: return "Lady Mechet";
	case 403: return "Lady Jadeth";
	case 404: return "Lady Miar";
	case 405: return "Lady Dria";
	case 406: return "Lady Glunde";
	case 407: return "Lady Loeka";
	case 408: return "Lady Bryn";
	case 409: return "Lady Eir";
	case 410: return "Lady Thera";
	case 411: return "Lady Hild";
	case 412: return "Lady Endegrid";
	case 413: return "Lady Herjasa";
	case 414: return "Lady Svipul";
	case 415: return "Lady Ingunn";
	case 416: return "Lady Kaeteli";
	case 417: return "Lady Eilif";
	case 418: return "Lady Gudrun";
	case 419: return "Lady Bergit";
	case 420: return "Lady Aesa";
	case 421: return "Lady Alfrun";
	case 422: return "Lady Afrid";
	case 423: return "Lady Brina";
	case 424: return "Lady Aliena";
	case 425: return "Lady Aneth";
	case 426: return "Lady Reada";
	case 427: return "Lady Saraten";
	case 428: return "Lady Baotheia";
	case 429: return "Lady Eleandra";
	case 430: return "Lady Meraced";
	case 431: return "Lady Adelisa";
	case 432: return "Lady Calantina";
	case 433: return "Lady Forbesa";
	case 434: return "Lady Claudora";
	case 435: return "Lady Anais";
	case 436: return "Lady Miraeia";
	case 437: return "Lady Agasia";
	case 438: return "Lady Geneiava";
	case 439: return "Lady Gwenael";
	case 440: return "Lady Ysueth";
	case 441: return "Lady Ellian";
	case 442: return "Lady Timethi";
	case 443: return "Lady Rayma";
	case 444: return "Lady Thanaikha";
	case 445: return "Lady Sulaha";
	case 446: return "Lady Shatha";
	case 447: return "Lady Bawthan";
	case 448: return "Lady Mahayl";
	case 449: return "Lady Isna";
	case 450: return "Lady Siyafan";
	case 451: return "Lady Ifar";
	case 452: return "Lady Yasmin";
	case 453: return "Lady Dula";
	case 454: return "Lady Ruwa";
	case 455: return "Lady Luqa";
	case 456: return "Lady Zandina";
	case 457: return "Lady Lulya";
	case 458: return "Lady Zahara";
	case 459: return "Lady Safiya";
	case 460: return "Lady Khalisa";
	case 461: return "Lady Janab";
	case 462: return "Lady Sur";
	case 463: return "Heroes End";
	case 464: return "Seneschal";
	case 465: return "Seneschal";
	case 466: return "Seneschal";
	case 467: return "Seneschal";
	case 468: return "Seneschal";
	case 469: return "Seneschal";
	case 470: return "Seneschal";
	case 471: return "Seneschal";
	case 472: return "Seneschal";
	case 473: return "Seneschal";
	case 474: return "Seneschal";
	case 475: return "Seneschal";
	case 476: return "Seneschal";
	case 477: return "Seneschal";
	case 478: return "Seneschal";
	case 479: return "Seneschal";
	case 480: return "Seneschal";
	case 481: return "Seneschal";
	case 482: return "Seneschal";
	case 483: return "Seneschal";
	case 484: return "Seneschal";
	case 485: return "Seneschal";
	case 486: return "Seneschal";
	case 487: return "Seneschal";
	case 488: return "Seneschal";
	case 489: return "Seneschal";
	case 490: return "Seneschal";
	case 491: return "Seneschal";
	case 492: return "Seneschal";
	case 493: return "Seneschal";
	case 494: return "Seneschal";
	case 495: return "Seneschal";
	case 496: return "Seneschal";
	case 497: return "Seneschal";
	case 498: return "Seneschal";
	case 499: return "Seneschal";
	case 500: return "Seneschal";
	case 501: return "Seneschal";
	case 502: return "Seneschal";
	case 503: return "Seneschal";
	case 504: return "Seneschal";
	case 505: return "Seneschal";
	case 506: return "Seneschal";
	case 507: return "Seneschal";
	case 508: return "Seneschal";
	case 509: return "Seneschal";
	case 510: return "Seneschal";
	case 511: return "Seneschal";
	case 512: return "Seneschal";
	case 513: return "Seneschal";
	case 514: return "Seneschal";
	case 515: return "Seneschal";
	case 516: return "Seneschal";
	case 517: return "Seneschal";
	case 518: return "Seneschal";
	case 519: return "Seneschal";
	case 520: return "Seneschal";
	case 521: return "Seneschal";
	case 522: return "Seneschal";
	case 523: return "Seneschal";
	case 524: return "Seneschal";
	case 525: return "Seneschal";
	case 526: return "Seneschal";
	case 527: return "Seneschal";
	case 528: return "Seneschal";
	case 529: return "Seneschal";
	case 530: return "Seneschal";
	case 531: return "Seneschal";
	case 532: return "Seneschal";
	case 533: return "Seneschal";
	case 534: return "Tournament Master";
	case 535: return "Tournament Master";
	case 536: return "Tournament Master";
	case 537: return "Tournament Master";
	case 538: return "Tournament Master";
	case 539: return "Tournament Master";
	case 540: return "Tournament Master";
	case 541: return "Tournament Master";
	case 542: return "Tournament Master";
	case 543: return "Tournament Master";
	case 544: return "Tournament Master";
	case 545: return "Tournament Master";
	case 546: return "Tournament Master";
	case 547: return "Tournament Master";
	case 548: return "Tournament Master";
	case 549: return "Tournament Master";
	case 550: return "Tournament Master";
	case 551: return "Tournament Master";
	case 552: return "Tournament Master";
	case 553: return "Tournament Master";
	case 554: return "Tournament Master";
	case 555: return "Tournament Master";
	case 556: return "Armorer";
	case 557: return "Armorer";
	case 558: return "Armorer";
	case 559: return "Armorer";
	case 560: return "Armorer";
	case 561: return "Armorer";
	case 562: return "Armorer";
	case 563: return "Armorer";
	case 564: return "Armorer";
	case 565: return "Armorer";
	case 566: return "Armorer";
	case 567: return "Armorer";
	case 568: return "Armorer";
	case 569: return "Armorer";
	case 570: return "Armorer";
	case 571: return "Armorer";
	case 572: return "Armorer";
	case 573: return "Armorer";
	case 574: return "Armorer";
	case 575: return "Armorer";
	case 576: return "Armorer";
	case 577: return "Armorer";
	case 578: return "Weaponsmith";
	case 579: return "Weaponsmith";
	case 580: return "Weaponsmith";
	case 581: return "Weaponsmith";
	case 582: return "Weaponsmith";
	case 583: return "Weaponsmith";
	case 584: return "Weaponsmith";
	case 585: return "Weaponsmith";
	case 586: return "Weaponsmith";
	case 587: return "Weaponsmith";
	case 588: return "Weaponsmith";
	case 589: return "Weaponsmith";
	case 590: return "Weaponsmith";
	case 591: return "Weaponsmith";
	case 592: return "Weaponsmith";
	case 593: return "Weaponsmith";
	case 594: return "Weaponsmith";
	case 595: return "Weaponsmith";
	case 596: return "Weaponsmith";
	case 597: return "Weaponsmith";
	case 598: return "Weaponsmith";
	case 599: return "Weaponsmith";
	case 600: return "Tavern Keeper";
	case 601: return "Tavern Keeper";
	case 602: return "Tavern Keeper";
	case 603: return "Tavern Keeper";
	case 604: return "Tavern Keeper";
	case 605: return "Tavern Keeper";
	case 606: return "Tavern Keeper";
	case 607: return "Tavern Keeper";
	case 608: return "Tavern Keeper";
	case 609: return "Tavern Keeper";
	case 610: return "Tavern Keeper";
	case 611: return "Tavern Keeper";
	case 612: return "Tavern Keeper";
	case 613: return "Tavern Keeper";
	case 614: return "Tavern Keeper";
	case 615: return "Tavern Keeper";
	case 616: return "Tavern Keeper";
	case 617: return "Tavern Keeper";
	case 618: return "Tavern Keeper";
	case 619: return "Tavern Keeper";
	case 620: return "Tavern Keeper";
	case 621: return "Tavern Keeper";
	case 622: return "Merchant";
	case 623: return "Merchant";
	case 624: return "Merchant";
	case 625: return "Merchant";
	case 626: return "Merchant";
	case 627: return "Merchant";
	case 628: return "Merchant";
	case 629: return "Merchant";
	case 630: return "Merchant";
	case 631: return "Merchant";
	case 632: return "Merchant";
	case 633: return "Merchant";
	case 634: return "Merchant";
	case 635: return "Merchant";
	case 636: return "Merchant";
	case 637: return "Merchant";
	case 638: return "Merchant";
	case 639: return "Merchant";
	case 640: return "Merchant";
	case 641: return "Merchant";
	case 642: return "Merchant";
	case 643: return "Merchant";
	case 644: return "Barezan";
	case 645: return "Horse Merchant";
	case 646: return "Horse Merchant";
	case 647: return "Horse Merchant";
	case 648: return "Horse Merchant";
	case 649: return "Horse Merchant";
	case 650: return "Horse Merchant";
	case 651: return "Horse Merchant";
	case 652: return "Horse Merchant";
	case 653: return "Horse Merchant";
	case 654: return "Horse Merchant";
	case 655: return "Horse Merchant";
	case 656: return "Horse Merchant";
	case 657: return "Horse Merchant";
	case 658: return "Horse Merchant";
	case 659: return "Horse Merchant";
	case 660: return "Horse Merchant";
	case 661: return "Horse Merchant";
	case 662: return "Horse Merchant";
	case 663: return "Horse Merchant";
	case 664: return "Horse Merchant";
	case 665: return "Horse Merchant";
	case 666: return "Horse Merchant";
	case 667: return "Guild Master";
	case 668: return "Guild Master";
	case 669: return "Guild Master";
	case 670: return "Guild Master";
	case 671: return "Guild Master";
	case 672: return "Guild Master";
	case 673: return "Guild Master";
	case 674: return "Guild Master";
	case 675: return "Guild Master";
	case 676: return "Guild Master";
	case 677: return "Guild Master";
	case 678: return "Guild Master";
	case 679: return "Guild Master";
	case 680: return "Guild Master";
	case 681: return "Guild Master";
	case 682: return "Guild Master";
	case 683: return "Guild Master";
	case 684: return "Guild Master";
	case 685: return "Guild Master";
	case 686: return "Guild Master";
	case 687: return "Guild Master";
	case 688: return "Guild Master";
	case 689: return "Village Elder";
	case 690: return "Village Elder";
	case 691: return "Village Elder";
	case 692: return "Village Elder";
	case 693: return "Village Elder";
	case 694: return "Village Elder";
	case 695: return "Village Elder";
	case 696: return "Village Elder";
	case 697: return "Village Elder";
	case 698: return "Village Elder";
	case 699: return "Village Elder";
	case 700: return "Village Elder";
	case 701: return "Village Elder";
	case 702: return "Village Elder";
	case 703: return "Village Elder";
	case 704: return "Village Elder";
	case 705: return "Village Elder";
	case 706: return "Village Elder";
	case 707: return "Village Elder";
	case 708: return "Village Elder";
	case 709: return "Village Elder";
	case 710: return "Village Elder";
	case 711: return "Village Elder";
	case 712: return "Village Elder";
	case 713: return "Village Elder";
	case 714: return "Village Elder";
	case 715: return "Village Elder";
	case 716: return "Village Elder";
	case 717: return "Village Elder";
	case 718: return "Village Elder";
	case 719: return "Village Elder";
	case 720: return "Village Elder";
	case 721: return "Village Elder";
	case 722: return "Village Elder";
	case 723: return "Village Elder";
	case 724: return "Village Elder";
	case 725: return "Village Elder";
	case 726: return "Village Elder";
	case 727: return "Village Elder";
	case 728: return "Village Elder";
	case 729: return "Village Elder";
	case 730: return "Village Elder";
	case 731: return "Village Elder";
	case 732: return "Village Elder";
	case 733: return "Village Elder";
	case 734: return "Village Elder";
	case 735: return "Village Elder";
	case 736: return "Village Elder";
	case 737: return "Village Elder";
	case 738: return "Village Elder";
	case 739: return "Village Elder";
	case 740: return "Village Elder";
	case 741: return "Village Elder";
	case 742: return "Village Elder";
	case 743: return "Village Elder";
	case 744: return "Village Elder";
	case 745: return "Village Elder";
	case 746: return "Village Elder";
	case 747: return "Village Elder";
	case 748: return "Village Elder";
	case 749: return "Village Elder";
	case 750: return "Village Elder";
	case 751: return "Village Elder";
	case 752: return "Village Elder";
	case 753: return "Village Elder";
	case 754: return "Village Elder";
	case 755: return "Village Elder";
	case 756: return "Village Elder";
	case 757: return "Village Elder";
	case 758: return "Village Elder";
	case 759: return "Village Elder";
	case 760: return "Village Elder";
	case 761: return "Village Elder";
	case 762: return "Village Elder";
	case 763: return "Village Elder";
	case 764: return "Village Elder";
	case 765: return "Village Elder";
	case 766: return "Village Elder";
	case 767: return "Village Elder";
	case 768: return "Village Elder";
	case 769: return "Village Elder";
	case 770: return "Village Elder";
	case 771: return "Village Elder";
	case 772: return "Village Elder";
	case 773: return "Village Elder";
	case 774: return "Village Elder";
	case 775: return "Village Elder";
	case 776: return "Village Elder";
	case 777: return "Village Elder";
	case 778: return "Village Elder";
	case 779: return "Village Elder";
	case 780: return "Village Elder";
	case 781: return "Village Elder";
	case 782: return "Village Elder";
	case 783: return "Village Elder";
	case 784: return "Village Elder";
	case 785: return "Village Elder";
	case 786: return "Village Elder";
	case 787: return "Village Elder";
	case 788: return "Village Elder";
	case 789: return "Village Elder";
	case 790: return "Village Elder";
	case 791: return "Village Elder";
	case 792: return "Village Elder";
	case 793: return "Village Elder";
	case 794: return "Village Elder";
	case 795: return "Village Elder";
	case 796: return "Village Elder";
	case 797: return "Village Elder";
	case 798: return "Village Elder";
	case 799: return "Merchants End";
	case 800: return "Craftsman";
	case 801: return "Craftsman";
	case 802: return "Craftsman";
	case 803: return "Craftsman";
	case 804: return "Craftsman";
	case 805: return "Craftsman";
	case 806: return "Craftsman";
	case 807: return "Craftsman";
	case 808: return "Craftsman";
	case 809: return "Craftsman";
	case 810: return "Craftsman";
	case 811: return "Seneschal";
	case 812: return "Seneschal";
	case 813: return "Seneschal";
	case 814: return "Seneschal";
	case 815: return "Seneschal";
	case 816: return "Seneschal";
	case 817: return "Seneschal";
	case 818: return "Seneschal";
	case 819: return "Seneschal";
	case 820: return "Seneschal";
	case 821: return "Seneschal";
	case 822: return "Zendar Chest";
	case 823: return "Melee Weapons Chest";
	case 824: return "Ranged Weapons Chest";
	case 825: return "Bonus Chest";
	case 826: return "Bonus Chest";
	case 827: return "Bonus Chest";
	case 828: return "Household Possessions";
	case 829: return "Temp Array A";
	case 830: return "Temp Array B";
	case 831: return "Temp Array C";
	case 832: return "Stack Selection Amounts";
	case 833: return "Stack Selection IDs";
	case 834: return "Notification Menu Types";
	case 835: return "Notification Menu Var1";
	case 836: return "Notification Menu Var2";
	case 837: return "Banner Background Color Array";
	case 838: return "Multiplayer Data";
	case 839: return "Local Merchant";
	case 840: return "Peasant Rebel";
	case 841: return "Peasant";
	case 842: return "Nervous Man";
	case 843: return "Belligerent Drunk";
	case 844: return "Hired Assassin";
	case 845: return "Rough-Looking Character";
	case 846: return "Ordinary Townsman";
	case 847: return "Unremarkable Townsman";
	case 848: return "Nurse";
	case 849: return "Minister";
	case 850: return "Quick Battle 6 Player";
	case 851: return "Swadian Crossbowman";
	case 852: return "Swadian Infantry";
	case 853: return "Swadian Man at Arms";
	case 854: return "Vaegir Archer";
	case 855: return "Vaegir Spearman";
	case 856: return "Vaegir Horseman";
	case 857: return "Khergit Dismounted Lancer";
	case 858: return "Khergit Horse Archer";
	case 859: return "Khergit Lancer";
	case 860: return "Nord Footman";
	case 861: return "Nord Scout";
	case 862: return "Nord Archer";
	case 863: return "Rhodok Crossbowman";
	case 864: return "Rhodok Spearman";
	case 865: return "Rhodok Scout";
	case 866: return "Sarranid Infantry";
	case 867: return "Sarranid Archer";
	case 868: return "Sarranid Horseman";
	case 869: return "Swadian Crossbowman";
	case 870: return "Swadian Infantry";
	case 871: return "Swadian Man at Arms";
	case 872: return "Vaegir Archer";
	case 873: return "Vaegir Spearman";
	case 874: return "Vaegir Horseman";
	case 875: return "Khergit Horse Archer";
	case 876: return "Khergit Infantry";
	case 877: return "Khergit Lancer";
	case 878: return "Nord Archer";
	case 879: return "Nord Huscarl";
	case 880: return "Nord Scout";
	case 881: return "Rhodok Crossbowman";
	case 882: return "Rhodok Sergeant";
	case 883: return "Rhodok Horseman";
	case 884: return "Sarranid Archer";
	case 885: return "Sarranid Footman";
	case 886: return "Sarranid Mamluke";
	case 887: return "Multiplayer End";
	case 888: return "Local Merchant";
	case 889: return "Local Merchant";
	case 890: return "Local Merchant";
	case 891: return "Local Merchant";
	case 892: return "Local Merchant";
	case 893: return "Local Merchant";
	case 894: return "Local Merchant";
	case 895: return "Local Merchant";
	case 896: return "Local Merchant";
	case 897: return "Rodrigo de Braganca";
	case 898: return "Usiatra";
	case 899: return "Hegen";
	case 900: return "Konrad";
	case 901: return "Sverre";
	case 902: return "Borislav";
	case 903: return "Stavros";
	case 904: return "Gamara";
	case 905: return "Aethrod";
	case 906: return "Zaira";
	case 907: return "Argo Sendnar";
	case 908: return "Quick Battle Troops End";
	case 909: return "Novice Fighter";
	case 910: return "Novice Fighter";
	case 911: return "Regular Fighter";
	case 912: return "Veteran Fighter";
	case 913: return "Archer";
	case 914: return "Archery Trainer";
	case 915: return "Rider";
	case 916: return "Horse Archer";
	case 917: return "Riding Trainer";
	case 918: return "Merchant of Praven";
	case 919: return "Merchant of Reyvadin";
	case 920: return "Merchant of Tulga";
	case 921: return "Merchant of Sargoth";
	case 922: return "Merchant of Jelkala";
	case 923: return "Merchant of Shariz";
	case 924: return "Startup Merchants End";
	case 925: return "Sea Raider Captain";
	case 926: return "Robber";
	case 927: return "Bandit Leaders End";
	case 928: return "Merchant's Brother";
	case 929: return "Relative of Merchants End";
	case 930: return "Swadian Crossbowman";
	case 931: return "Swadian Infantry";
	case 932: return "Swadian Man at Arms";
	case 933: return "Vaegir Archer";
	case 934: return "Vaegir Spearman";
	case 935: return "Vaegir Horseman";
	case 936: return "Khergit Horse Archer";
	case 937: return "Khergit Infantry";
	case 938: return "Khergit Lancer";
	case 939: return "Nord Archer";
	case 940: return "Nord Huscarl";
	case 941: return "Nord Scout";
	case 942: return "Rhodok Crossbowman";
	case 943: return "Rhodok Sergeant";
	case 944: return "Rhodok Horseman";
	case 945: return "Sarranid Archer";
	case 946: return "Sarranid Footman";
	case 947: return "Sarranid Mamluke";
	case 948: return "Swadian Crossbowman";
	case 949: return "Swadian Infantry";
	case 950: return "Swadian Man at Arms";
	case 951: return "Vaegir Archer";
	case 952: return "Vaegir Spearman";
	case 953: return "Vaegir Horseman";
	case 954: return "Khergit Horse Archer";
	case 955: return "Khergit Infantry";
	case 956: return "Khergit Lancer";
	case 957: return "Nord Archer";
	case 958: return "Nord Huscarl";
	case 959: return "Nord Scout";
	case 960: return "Rhodok Crossbowman";
	case 961: return "Rhodok Sergeant";
	case 962: return "Rhodok Horseman";
	case 963: return "Sarranid Archer";
	case 964: return "Sarranid Footman";
	case 965: return "Sarranid Mamluke";
	case 966: return "Swadian Crossbowman";
	case 967: return "Swadian Infantry";
	case 968: return "Swadian Man at Arms";
	case 969: return "Vaegir Archer";
	case 970: return "Vaegir Spearman";
	case 971: return "Vaegir Horseman";
	case 972: return "Khergit Horse Archer";
	case 973: return "Khergit Infantry";
	case 974: return "Khergit Lancer";
	case 975: return "Nord Archer";
	case 976: return "Nord Huscarl";
	case 977: return "Nord Scout";
	case 978: return "Rhodok Crossbowman";
	case 979: return "Rhodok Sergeant";
	case 980: return "Rhodok Horseman";
	case 981: return "Sarranid Archer";
	case 982: return "Sarranid Footman";
	case 983: return "Sarranid Mamluke";
	case 984: return "Swadian Crossbowman";
	case 985: return "Swadian Infantry";
	case 986: return "Swadian Man at Arms";
	case 987: return "Vaegir Archer";
	case 988: return "Vaegir Spearman";
	case 989: return "Vaegir Horseman";
	case 990: return "Khergit Horse Archer";
	case 991: return "Khergit Infantry";
	case 992: return "Khergit Lancer";
	case 993: return "Nord Archer";
	case 994: return "Nord Huscarl";
	case 995: return "Nord Scout";
	case 996: return "Rhodok Crossbowman";
	case 997: return "Rhodok Sergeant";
	case 998: return "Rhodok Horseman";
	case 999: return "Sarranid Archer";
	case 1000: return "Sarranid Footman";
	case 1001: return "Sarranid Mamluke";
	case 1002: return "Multiplayer End";
	case 1003: return "Borcha";
	case 1004: return "Marnid";
	case 1005: return "Ymira";
	case 1006: return "Rolf";
	case 1007: return "Baheshtur";
	case 1008: return "Firentis";
	case 1009: return "Deshavi";
	case 1010: return "Matheld";
	case 1011: return "Alayen";
	case 1012: return "Bunduk";
	case 1013: return "Katrin";
	case 1014: return "Jeremus";
	case 1015: return "Nizar";
	case 1016: return "Lezalit";
	case 1017: return "Artimenner";
	case 1018: return "Klethi";
	case 1019: return "Borcha";
	case 1020: return "Marnid";
	case 1021: return "Ymira";
	case 1022: return "Rolf";
	case 1023: return "Baheshtur";
	case 1024: return "Firentis";
	case 1025: return "Deshavi";
	case 1026: return "Matheld";
	case 1027: return "Alayen";
	case 1028: return "Bunduk";
	case 1029: return "Katrin";
	case 1030: return "Jeremus";
	case 1031: return "Nizar";
	case 1032: return "Lezalit";
	case 1033: return "Artimenner";
	case 1034: return "Klethi";
	case 1035: return "Borcha";
	case 1036: return "Marnid";
	case 1037: return "Ymira";
	case 1038: return "Rolf";
	case 1039: return "Baheshtur";
	case 1040: return "Firentis";
	case 1041: return "Deshavi";
	case 1042: return "Matheld";
	case 1043: return "Alayen";
	case 1044: return "Bunduk";
	case 1045: return "Katrin";
	case 1046: return "Jeremus";
	case 1047: return "Nizar";
	case 1048: return "Lezalit";
	case 1049: return "Artimenner";
	case 1050: return "Klethi";
	case 1051: return "Borcha";
	case 1052: return "Marnid";
	case 1053: return "Ymira";
	case 1054: return "Rolf";
	case 1055: return "Baheshtur";
	case 1056: return "Firentis";
	case 1057: return "Deshavi";
	case 1058: return "Matheld";
	case 1059: return "Alayen";
	case 1060: return "Bunduk";
	case 1061: return "Katrin";
	case 1062: return "Jeremus";
	case 1063: return "Nizar";
	case 1064: return "Lezalit";
	case 1065: return "Artimenner";
	case 1066: return "Klethi";
	case 1067: return "Multiplayer End";
	case 1068: return "Multiplayer End";
	case 1069: return "Multiplayer End";
	case 1070: return "Multiplayer End";
	case 1071: return "Multiplayer End";
	default: return "ERROR";
	}
}

int UnitExpense(int ID) {
	return 2;//table for unit expenses
}

std::string FactionDecoder(int ID, std::string PlayerFaction) {
	switch (ID) {
	case 0: return "No Faction";
	case 1: return "Commoners";
	case 2: return "Outlaws";
	case 3: return "Neutral";
	case 4: return "Innocents";
	case 5: return "Merchants";
	case 6: return "Dark Knights";
	case 7: return "Culture 1";
	case 8: return "Culture 2";
	case 9: return "Culture 3";
	case 10: return "Culture 4";
	case 11: return "Culture 5";
	case 12: return "Culture 6";
	case 13: {
		if (PlayerFaction == "Player's Supporters") return "Player Faction";
		else return PlayerFaction;
	}
	case 14: {
		if (PlayerFaction == "Player's Supporters") return "Player Faction";
		else return PlayerFaction;
	}
	case 15: return "Kingdom of Swadia";
	case 16: return "Kingdom of Vaegirs";
	case 17: return "Khergit Khanate";
	case 18: return "Kingdom of Nords";
	case 19: return "Kingdom of Rhodoks";
	case 20: return "Sarranid Sultanate";
	case 21: return "Kingdoms End";
	case 22: return "Robber Knights";
	case 23: return "Khergits";
	case 24: return "Black Khergits";
	case 25: return "Manhunters";
	case 26: return "Deserters";
	case 27: return "Mountain Bandits";
	case 28: return "Forest Bandits";
	case 29: return "Undeads";
	case 30: return "Slavers";
	case 31: return "Peasant Rebels";
	case 32: return "Noble Refugees";
	case 33: return "All Stars";
	default: return "ERROR";
	}
}

std::string DecodeImp(int ID) {
	switch (ID) {
	case 130: return "Manor";
	case 131: return "Mill";
	case 132: return "Watch Tower";
	case 133: return "School";
	case 134: return "Messenger Post";
	case 135: return "Prison Tower";
	default: return "ERROR";
	}
}

class Unit {
public:
	Unit::Unit() {
		ID = -1;
		Type = "";
		Prisoner = false;
		Quantity = -1;
		Wounded = -1;
		Expense = -1;
	}

	void Unit::CalculateExpense() {
		if (Prisoner) Expense = 0;
		else Expense = Quantity * UnitExpense(ID);
	}

	int ID;
	std::string Type;
	bool Prisoner;
	int Quantity;
	int Wounded;
	int Expense;
};

class Place {
public:
	Place::Place() {
		Type = -1;
		Name = "";
		Faction = -1;
		Lord = -1;
		Relation = 0;
		Prosperity = 0;
		OriginalFaction = -1;
		CurrentImp = -1;
		ImpEndHour = -1;
		Manor = false;
		Mill = false;
		WatchT = false;
		School = false;
		Messenger = false;
		PrisonT = false;
		Enterprise = -1;
	}

	Place::~Place() {
		int j = Units.size();
		for (int i = j - 1; i >= 0; i--) {
			delete Units.at(i);
			Units.pop_back();
		}
	}

	int Type;
	std::string Name;
	int Faction;
	std::vector<Unit*> Units;
	long Lord;
	long Relation;
	long Prosperity;
	long OriginalFaction;
	long CurrentImp;
	long ImpEndHour;
	bool Manor;
	bool Mill;
	bool WatchT;
	bool School;
	bool Messenger;
	bool PrisonT;
	long Enterprise;
};

void Initialize(std::string& FilePath) {
	std::string Input;
	std::ifstream Option("Options.txt");

	if (Option.good()) std::getline(Option, FilePath);
	else FilePath = "No current directory";
	Option.close();

	std::cout << "Enter new save game directory, or leave blank to use current:\n" << FilePath << "\n";
	std::getline(std::cin, Input);

	if (Input != "") {
		FilePath = Input;
		std::ofstream NewOption("Options.txt");
		NewOption.clear();
		NewOption << FilePath << "\n";
		NewOption.close();
	}
}

std::string ReadFile(std::string FilePath) {
	std::string FileName = FilePath + "\\sg0";
	std::string Input;

	std::cout << "Save slot: ";
	std::getline(std::cin, Input);
	FileName.append(Input + ".sav");

	std::ifstream File(FileName, std::ios_base::binary);
	if (!File.good()) {
		std::cout << "Invalid save slot\n";
		return "";
	}

	std::string s = static_cast<std::stringstream const&>(std::stringstream() << File.rdbuf()).str();
	File.close();
	return s;
}

int Parse32Bit(std::string& Content, size_t& s) {
	std::string Temp = "";
	for (int i = 0; i < 4; i++) {
		Temp += Content.at(s);
		s++;
	}
	return FourLittleByteStringToInteger(Temp);
}

long Parse64Bit(std::string& Content, size_t& s) {
	std::string Temp = "";
	for (int i = 0; i < 8; i++) {
		Temp += Content.at(s);
		s++;
	}
	return EightLittleByteStringToInteger(Temp);
}

std::string ParseString(std::string& Content, size_t& s) {
	std::string S = "";
	int Size = Parse32Bit(Content, s);
	for (int i = 0; i < Size; i++) {
		S += Content.at(s);
		s++;
	}
	return S;
}

std::vector<Unit*> ParseUnits(std::string& Content, size_t& s) {
	std::vector<Unit*> V;
	int Num = Parse32Bit(Content, s);

	for (int i = 0; i < Num; i++) {
		Unit* U = new Unit();
		U->ID = Parse32Bit(Content, s);
		U->Quantity = Parse32Bit(Content, s);
		U->Wounded = Parse32Bit(Content, s);
		U->Prisoner = !!(Parse32Bit(Content, s)); //is prisoner the only non zero flag?
		U->CalculateExpense();
		V.push_back(U);
	}

	return V;
}

Place* ParsePlayer(std::string& Content, size_t& s) {
	Place* P = new Place();
	P->Type = 0;

	s = Content.find("p_main_party") + 12;

	P->Name = ParseString(Content, s);

	s += 16;
	P->Faction = Parse32Bit(Content, s);

	s += 48;
	P->Units = ParseUnits(Content, s);

	return P;
}

Place* ParseTown(std::string& Content, size_t& s) {
	Place* P = new Place();
	char c;

	size_t x = Content.find("p_town_", s);
	if (x == std::string::npos) return P;
	s = x;
	P->Type = 1;

	s -= 4;
	ParseString(Content, s);

	P->Name = ParseString(Content, s);

	s += 16;
	P->Faction = Parse32Bit(Content, s);

	s += 48;
	P->Units = ParseUnits(Content, s);

	s += 5;
	ParseString(Content, s);
	s += 77;
	for (int i = Parse32Bit(Content, s); i != 0; i--) s += 4;
	for (int i = Parse32Bit(Content, s); i != 0; i--) s += 4;
	for (int i = 0; i < 16; i++) {
		ParseString(Content, s);
		s += 9;
	}
	s += 60;

	P->Lord = Parse64Bit(Content, s);

	s += 144;
	P->Relation = Parse64Bit(Content, s);

	s += 184;
	P->Prosperity = Parse64Bit(Content, s);

	s += 80;
	P->OriginalFaction = Parse64Bit(Content, s);

	s += 496;
	P->CurrentImp = Parse64Bit(Content, s);

	P->ImpEndHour = Parse64Bit(Content, s);

	s += 64;
	P->Messenger = Parse64Bit(Content, s);

	P->PrisonT = Parse64Bit(Content, s);

	s += 8;
	P->Enterprise = Parse64Bit(Content, s);

	return P;
}

Place* ParseCastle(std::string& Content, size_t& s) {
	Place* P = new Place();
	char c;

	size_t x = Content.find("p_castle_", s);
	if (x == std::string::npos) return P;
	s = x;
	P->Type = 2;

	s -= 4;
	ParseString(Content, s);

	P->Name = ParseString(Content, s);

	s += 16;
	P->Faction = Parse32Bit(Content, s);

	s += 48;
	P->Units = ParseUnits(Content, s);

	s += 5;
	ParseString(Content, s);
	s += 77;
	for (int i = Parse32Bit(Content, s); i != 0; i--) s += 4;
	for (int i = Parse32Bit(Content, s); i != 0; i--) s += 4;
	for (int i = 0; i < 16; i++) {
		ParseString(Content, s);
		s += 9;
	}
	s += 60;

	P->Lord = Parse64Bit(Content, s);

	s += 336;
	P->Prosperity = Parse64Bit(Content, s);

	s += 80;
	P->OriginalFaction = Parse64Bit(Content, s);

	s += 496;
	P->CurrentImp = Parse64Bit(Content, s);

	P->ImpEndHour = Parse64Bit(Content, s);

	s += 64;
	P->Messenger = Parse64Bit(Content, s);

	P->PrisonT = Parse64Bit(Content, s);

	return P;
}

Place* ParseVillage(std::string& Content, size_t& s) {
	Place* P = new Place();
	char c;

	size_t x = Content.find("p_village_", s);
	if (x == std::string::npos) return P;
	s = x;
	P->Type = 3;

	s -= 4;
	ParseString(Content, s);

	P->Name = ParseString(Content, s);

	s += 16;
	P->Faction = Parse32Bit(Content, s);

	s += 48;
	ParseUnits(Content, s);

	s += 5;
	ParseString(Content, s);
	s += 77;
	for (int i = Parse32Bit(Content, s); i != 0; i--) s += 4;
	for (int i = Parse32Bit(Content, s); i != 0; i--) s += 4;
	for (int i = 0; i < 16; i++) {
		ParseString(Content, s);
		s += 9;
	}
	s += 60;

	P->Lord = Parse64Bit(Content, s);

	s += 144;
	P->Relation = Parse64Bit(Content, s);

	s += 184;
	P->Prosperity = Parse64Bit(Content, s);

	s += 80;
	P->OriginalFaction = Parse64Bit(Content, s);

	s += 496;
	P->CurrentImp = Parse64Bit(Content, s);

	P->ImpEndHour = Parse64Bit(Content, s);

	s += 32;
	P->Manor = Parse64Bit(Content, s);

	P->Mill = Parse64Bit(Content, s);

	P->WatchT = Parse64Bit(Content, s);

	P->School = Parse64Bit(Content, s);

	P->Messenger = Parse64Bit(Content, s);

	return P;
}

unsigned long ParseTimeAndName(std::string& Content, std::string& PlayerName, std::string& PlayerFaction) {
	size_t s = 0;

	s += 12;
	ParseString(Content, s);
	PlayerName = ParseString(Content, s);
	s += 8;

	unsigned long a = (unsigned long)Parse64Bit(Content, s);
	a = a / (unsigned long)100000;
	s += 19 * 4;
	ParseString(Content, s);
	s += 41;
	ParseString(Content, s);
	s += 48;
	for (int i = 0; i < 9; i++) ParseString(Content, s);
	int x = Parse32Bit(Content, s);
	s += x * 8;
	x = Parse32Bit(Content, s);
	s += x * 28;
	x = Parse32Bit(Content, s);
	s += x * 8;
	x = Parse32Bit(Content, s);
	for (int i = 0; i < x; i++) {
		s += 16;
		ParseString(Content, s);
		ParseString(Content, s);
		ParseString(Content, s);
		for (int j = 0; j < 16; j++) {
			ParseString(Content, s);
			s += 9;
		}
		int n = Parse32Bit(Content, s);
		s += n * 8;
	}
	x = Parse32Bit(Content, s);
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < 16; j++) {
			ParseString(Content, s);
			s += 9;
		}
	}
	x = Parse32Bit(Content, s);
	for (int i = 0; i < x; i++) {
		int n = Parse32Bit(Content, s);
		s += n * 8;
	}
	x = Parse32Bit(Content, s);

	s = Content.find("Player Faction") - 4;
	ParseString(Content, s);
	s += 9;
	for (int i = 0; i < 16; i++) {
		ParseString(Content, s);
		s += 9;
	}
	s += 8 * Parse32Bit(Content, s);
	s += 4 * x;
	PlayerFaction = ParseString(Content, s);

	return a;
}

std::vector<Place*> Parse(std::string& Content, unsigned long& Time, int& Towns, int& Castles, int& Villages, std::string& PlayerName, std::string& PlayerFaction) {
	size_t s = 0;
	std::vector<Place*> Data;
	Towns = 0;
	Castles = 0;
	Villages = 0;

	Time = ParseTimeAndName(Content, PlayerName, PlayerFaction);

	Data.push_back(ParsePlayer(Content, s));

	while (1) {
		Data.push_back(ParseTown(Content, s));
		if (Data.at(Data.size() - 1)->Type == -1) {
			Data.pop_back();
			break;
		}
		Towns++;
	}

	while (1) {
		Data.push_back(ParseCastle(Content, s));
		if (Data.at(Data.size() - 1)->Type == -1) {
			Data.pop_back();
			break;
		}
		Castles++;
	}

	while (1) {
		Data.push_back(ParseVillage(Content, s));
		if (Data.at(Data.size() - 1)->Type == -1) {
			Data.pop_back();
			break;
		}
		Villages++;
	}

	return Data;
}

std::string DecodeEnterprise(long ID) {
	switch (ID) {
	case 93: return "Oil Press";
	case 96: return "Linen Weavery";
	case 98: return "Wool Weavery";
	case 101: return "Dyeworks";
	case 103: return "Ironworks";
	case 105: return "Tannery";
	case 108: return "Wine Press";
	case 109: return "Brewery";
	case 121: return "Mill";
	default: return "No";
	}
}

void PrintData(std::vector<Place*>& Data, int Time, int Towns, int Castles, int Villages, std::string PlayerName, std::string PlayerFaction) {
	std::stringstream ss;
	std::string Temp;
	std::vector<Unit*> Army;
	std::vector<Unit*> Prisoners;

	ss << "Day " << (Time / 24) << "\n\n\nPLAYER\n\n\n";

	ss << "--" << Data.at(0)->Name << "--\n";
	ss << "  " << FactionDecoder(Data.at(0)->Faction, PlayerFaction) << "\n\n";
	for (int i = 0; i < Data.at(0)->Units.size(); i++) {
		if (Data.at(0)->Units.at(i)->Prisoner) Prisoners.push_back(Data.at(0)->Units.at(i));
		else Army.push_back(Data.at(0)->Units.at(i));
	}

	ss << " -Units-\n";
	int TotalCost = 0;
	int TotalNumber = 0;
	int TotalHealthy = 0;
	for (int i = 0; i < Army.size(); i++) {
		TotalNumber += Army.at(i)->Quantity;
		TotalCost += Army.at(i)->Expense;
		Temp = UnitType((long)Army.at(i)->ID, PlayerName);
		ss << "  " << Temp;
		for (int j = 0; j < (32 - Temp.size()); j++) ss << " ";

		int Healthy = Army.at(i)->Quantity - Army.at(i)->Wounded;
		TotalHealthy += Healthy;
		if (Healthy == 0) Healthy++;
		int HealthyDigits = 0;
		while (Healthy > 0) {
			Healthy = Healthy / 10;
			HealthyDigits++;
		}
		int LeftOffset = 4 - HealthyDigits;
		Healthy = Army.at(i)->Quantity - Army.at(i)->Wounded;

		int Total = Army.at(i)->Quantity;
		int TotalDigits = 0;
		while (Total > 0) {
			Total = Total / 10;
			TotalDigits++;
		}
		int RightOffset = 4 - TotalDigits;

		for (int j = 0; j < LeftOffset; j++) ss << " ";
		ss << Healthy;
		ss << " /";
		for (int j = 0; j < RightOffset; j++) ss << " ";
		ss << Army.at(i)->Quantity;

		/*
		std::stringstream tss;
		tss << Army.at(i)->Expense << "/week";
		TotalDigits = 20 - tss.str().size();
		for (int j = 0; j < TotalDigits; j++) ss << " ";
		ss << tss.str() << "\n";*/ ss << "\n";
	}

	if (Army.size() > 1) {
		ss << "\n";
		for (int i = 0; i < 1; i++) {
			int Dummy = TotalHealthy;
			if (Dummy == 0) Dummy = 1;
			int HealthyDigits = 0;
			while (Dummy > 0) {
				Dummy = Dummy / 10;
				HealthyDigits++;
			}
			int LeftOffset = 4 - HealthyDigits;

			Dummy = TotalNumber;
			int TotalDigits = 0;
			while (Dummy > 0) {
				Dummy = Dummy / 10;
				TotalDigits++;
			}
			int RightOffset = 4 - TotalDigits;

			std::stringstream tss;
			for (int j = 0; j < LeftOffset; j++) tss << " ";
			tss << TotalHealthy;
			tss << " /";
			for (int j = 0; j < RightOffset; j++) tss << " ";
			tss << TotalNumber;
			int Offset = 44 - tss.str().size();
			for (int j = 0; j < Offset; j++) ss << " ";
			ss << tss.str();
		}

		for (int i = 0; i < 1; i++) {
			/*std::stringstream tss;
			tss << TotalCost << "/week";
			int Offset = 20 - tss.str().size();
			for (int j = 0; j < Offset; j++) ss << " ";
			ss << tss.str();*/
			ss << "\n";
		}
	}

	TotalHealthy = 0;
	TotalNumber = 0;
	if (Prisoners.size() > 0) {
		ss << " -Prisoners-\n";
		for (int i = 0; i < Prisoners.size(); i++) {
			Temp = UnitType((long)Prisoners.at(i)->ID, PlayerName);
			ss << "  " << Temp;
			for (int j = 0; j < (32 - Temp.size()); j++) ss << " ";

			int Healthy = Prisoners.at(i)->Quantity - Prisoners.at(i)->Wounded;
			TotalHealthy += Healthy;
			if (Healthy == 0) Healthy++;
			int HealthyDigits = 0;
			while (Healthy > 0) {
				Healthy = Healthy / 10;
				HealthyDigits++;
			}
			int LeftOffset = 4 - HealthyDigits;
			Healthy = Prisoners.at(i)->Quantity - Prisoners.at(i)->Wounded;

			int Total = Prisoners.at(i)->Quantity;
			TotalNumber += Total;
			int TotalDigits = 0;
			while (Total > 0) {
				Total = Total / 10;
				TotalDigits++;
			}
			int RightOffset = 4 - TotalDigits;

			for (int j = 0; j < LeftOffset; j++) ss << " ";
			ss << Healthy;
			ss << " /";
			for (int j = 0; j < RightOffset; j++) ss << " ";
			ss << Prisoners.at(i)->Quantity << "\n";
		}
	}

	if (Prisoners.size() > 1) {
		ss << "\n";
		for (int i = 0; i < 1; i++) {
			int Dummy = TotalHealthy;
			if (Dummy == 0) Dummy = 1;
			int HealthyDigits = 0;
			while (Dummy > 0) {
				Dummy = Dummy / 10;
				HealthyDigits++;
			}
			int LeftOffset = 4 - HealthyDigits;

			Dummy = TotalNumber;
			int TotalDigits = 0;
			while (Dummy > 0) {
				Dummy = Dummy / 10;
				TotalDigits++;
			}
			int RightOffset = 4 - TotalDigits;

			std::stringstream tss;
			for (int j = 0; j < LeftOffset; j++) tss << " ";
			tss << TotalHealthy;
			tss << " /";
			for (int j = 0; j < RightOffset; j++) tss << " ";
			tss << TotalNumber;
			int Offset = 44 - tss.str().size();
			for (int j = 0; j < Offset; j++) ss << " ";
			ss << tss.str();
			ss << "\n";
		}
	}

	ss << "\n\nTOWNS\n\n\n";
	//TOWNS START HERE
	for (int z = 15; z < 21; z++) {
		for (int q = 1; q < Towns + 1; q++) {
			if (Data.at(q)->OriginalFaction == z && Data.at(q)->Lord == 0) {
				Army.clear();
				Prisoners.clear();
				ss << "--" << Data.at(q)->Name << "--\n";
				ss << "  " << FactionDecoder(Data.at(q)->Faction, PlayerFaction) << "\n";
				ss << "  " << UnitType(Data.at(q)->Lord, PlayerName) << "\n\n";
				ss << "  " << "Relation                              " << Data.at(q)->Relation << "\n";
				ss << "  " << "Prosperity                            " << Data.at(q)->Prosperity << "\n\n";
				ss << "  " << "Messenger Post                        ";
				if (Data.at(q)->Messenger) ss << "Yes\n";
				else if (Data.at(q)->CurrentImp == 134) ss << "Building, " << (Data.at(q)->ImpEndHour - Time) / 24 << " days\n";
				else ss << "No\n";

				ss << "  " << "Prisoner Tower                        ";
				if (Data.at(q)->PrisonT) ss << "Yes\n\n";
				else if (Data.at(q)->CurrentImp == 135) ss << "Building, " << (Data.at(q)->ImpEndHour - Time) / 24 << " days\n\n";
				else ss << "No\n";

				ss << "  " << "Player Enterprise                     " << DecodeEnterprise(Data.at(q)->Enterprise) << "\n\n";

				for (int i = 0; i < Data.at(q)->Units.size(); i++) {
					if (Data.at(q)->Units.at(i)->Prisoner) Prisoners.push_back(Data.at(q)->Units.at(i));
					else Army.push_back(Data.at(q)->Units.at(i));
				}

				ss << " -Units-\n";
				int TotalCost = 0;
				int TotalNumber = 0;
				int TotalHealthy = 0;
				for (int i = 0; i < Army.size(); i++) {
					TotalNumber += Army.at(i)->Quantity;
					TotalCost += Army.at(i)->Expense;
					Temp = UnitType((long)Army.at(i)->ID, PlayerName);
					ss << "  " << Temp;
					for (int j = 0; j < (32 - Temp.size()); j++) ss << " ";

					int Healthy = Army.at(i)->Quantity - Army.at(i)->Wounded;
					TotalHealthy += Healthy;
					if (Healthy == 0) Healthy++;
					int HealthyDigits = 0;
					while (Healthy > 0) {
						Healthy = Healthy / 10;
						HealthyDigits++;
					}
					int LeftOffset = 4 - HealthyDigits;
					Healthy = Army.at(i)->Quantity - Army.at(i)->Wounded;

					int Total = Army.at(i)->Quantity;
					int TotalDigits = 0;
					while (Total > 0) {
						Total = Total / 10;
						TotalDigits++;
					}
					int RightOffset = 4 - TotalDigits;

					for (int j = 0; j < LeftOffset; j++) ss << " ";
					ss << Healthy;
					ss << " /";
					for (int j = 0; j < RightOffset; j++) ss << " ";
					ss << Army.at(i)->Quantity;

					/*
					std::stringstream tss;
					tss << Army.at(i)->Expense << "/week";
					TotalDigits = 20 - tss.str().size();
					for (int j = 0; j < TotalDigits; j++) ss << " ";
					ss << tss.str() << "\n";*/ ss << "\n";
				}

				if (Army.size() > 1) {
					ss << "\n";
					for (int i = 0; i < 1; i++) {
						int Dummy = TotalHealthy;
						if (Dummy == 0) Dummy = 1;
						int HealthyDigits = 0;
						while (Dummy > 0) {
							Dummy = Dummy / 10;
							HealthyDigits++;
						}
						int LeftOffset = 4 - HealthyDigits;

						Dummy = TotalNumber;
						int TotalDigits = 0;
						while (Dummy > 0) {
							Dummy = Dummy / 10;
							TotalDigits++;
						}
						int RightOffset = 4 - TotalDigits;

						std::stringstream tss;
						for (int j = 0; j < LeftOffset; j++) tss << " ";
						tss << TotalHealthy;
						tss << " /";
						for (int j = 0; j < RightOffset; j++) tss << " ";
						tss << TotalNumber;
						int Offset = 44 - tss.str().size();
						for (int j = 0; j < Offset; j++) ss << " ";
						ss << tss.str();
					}

					for (int i = 0; i < 1; i++) {
						/*std::stringstream tss;
						tss << TotalCost << "/week";
						int Offset = 20 - tss.str().size();
						for (int j = 0; j < Offset; j++) ss << " ";
						ss << tss.str();*/
					}
				}

				if (Army.size() < 2) ss << "\n";

				TotalHealthy = 0;
				TotalNumber = 0;
				if (Prisoners.size() > 0) {
					ss << "\n -Prisoners-\n";
					for (int i = 0; i < Prisoners.size(); i++) {
						Temp = UnitType((long)Prisoners.at(i)->ID, PlayerName);
						ss << "  " << Temp;
						for (int j = 0; j < (32 - Temp.size()); j++) ss << " ";

						int Healthy = Prisoners.at(i)->Quantity - Prisoners.at(i)->Wounded;
						TotalHealthy += Healthy;
						if (Healthy == 0) Healthy++;
						int HealthyDigits = 0;
						while (Healthy > 0) {
							Healthy = Healthy / 10;
							HealthyDigits++;
						}
						int LeftOffset = 4 - HealthyDigits;
						Healthy = Prisoners.at(i)->Quantity - Prisoners.at(i)->Wounded;

						int Total = Prisoners.at(i)->Quantity;
						TotalNumber += Total;
						int TotalDigits = 0;
						while (Total > 0) {
							Total = Total / 10;
							TotalDigits++;
						}
						int RightOffset = 4 - TotalDigits;

						for (int j = 0; j < LeftOffset; j++) ss << " ";
						ss << Healthy;
						ss << " /";
						for (int j = 0; j < RightOffset; j++) ss << " ";
						ss << Prisoners.at(i)->Quantity << "\n";
					}
				}

				if (Prisoners.size() > 1) {
					ss << "\n";
					for (int i = 0; i < 1; i++) {
						int Dummy = TotalHealthy;
						if (Dummy == 0) Dummy = 1;
						int HealthyDigits = 0;
						while (Dummy > 0) {
							Dummy = Dummy / 10;
							HealthyDigits++;
						}
						int LeftOffset = 4 - HealthyDigits;

						Dummy = TotalNumber;
						int TotalDigits = 0;
						while (Dummy > 0) {
							Dummy = Dummy / 10;
							TotalDigits++;
						}
						int RightOffset = 4 - TotalDigits;

						std::stringstream tss;
						for (int j = 0; j < LeftOffset; j++) tss << " ";
						tss << TotalHealthy;
						tss << " /";
						for (int j = 0; j < RightOffset; j++) tss << " ";
						tss << TotalNumber;
						int Offset = 44 - tss.str().size();
						for (int j = 0; j < Offset; j++) ss << " ";
						ss << tss.str();
					}
				}

				if (Prisoners.size() > 0) ss << "\n";
				if (Prisoners.size() < 1) ss << "\n";

				ss << "\n\n";
			}
		}
	}
	ss << "CASTLES\n\n\n";
	//CASTLES START HERE
	for (int z = 15; z < 21; z++) {
		for (int q = 1 + Towns; q < 1 + Towns + Castles; q++) {
			if (Data.at(q)->OriginalFaction == z && Data.at(q)->Lord == 0) {
				Army.clear();
				Prisoners.clear();
				ss << "--" << Data.at(q)->Name << "--\n";
				ss << "  " << FactionDecoder(Data.at(q)->Faction, PlayerFaction) << "\n";
				ss << "  " << UnitType(Data.at(q)->Lord, PlayerName) << "\n\n";
				ss << "  " << "Prosperity                            " << Data.at(q)->Prosperity << "\n\n";
				ss << "  " << "Messenger Post                        ";
				if (Data.at(q)->Messenger) ss << "Yes\n";
				else if (Data.at(q)->CurrentImp == 134) ss << "Building, " << (Data.at(q)->ImpEndHour - Time) / 24 << " days\n";
				else ss << "No\n";

				ss << "  " << "Prisoner Tower                        ";
				if (Data.at(q)->PrisonT) ss << "Yes\n\n";
				else if (Data.at(q)->CurrentImp == 135) ss << "Building, " << (Data.at(q)->ImpEndHour - Time) / 24 << " days\n\n";
				else ss << "No\n\n";

				for (int i = 0; i < Data.at(q)->Units.size(); i++) {
					if (Data.at(q)->Units.at(i)->Prisoner) Prisoners.push_back(Data.at(q)->Units.at(i));
					else Army.push_back(Data.at(q)->Units.at(i));
				}

				ss << " -Units-\n";
				int TotalCost = 0;
				int TotalNumber = 0;
				int TotalHealthy = 0;
				for (int i = 0; i < Army.size(); i++) {
					TotalNumber += Army.at(i)->Quantity;
					TotalCost += Army.at(i)->Expense;
					Temp = UnitType((long)Army.at(i)->ID, PlayerName);
					ss << "  " << Temp;
					for (int j = 0; j < (32 - Temp.size()); j++) ss << " ";

					int Healthy = Army.at(i)->Quantity - Army.at(i)->Wounded;
					TotalHealthy += Healthy;
					if (Healthy == 0) Healthy++;
					int HealthyDigits = 0;
					while (Healthy > 0) {
						Healthy = Healthy / 10;
						HealthyDigits++;
					}
					int LeftOffset = 4 - HealthyDigits;
					Healthy = Army.at(i)->Quantity - Army.at(i)->Wounded;

					int Total = Army.at(i)->Quantity;
					int TotalDigits = 0;
					while (Total > 0) {
						Total = Total / 10;
						TotalDigits++;
					}
					int RightOffset = 4 - TotalDigits;

					for (int j = 0; j < LeftOffset; j++) ss << " ";
					ss << Healthy;
					ss << " /";
					for (int j = 0; j < RightOffset; j++) ss << " ";
					ss << Army.at(i)->Quantity;

					/*
					std::stringstream tss;
					tss << Army.at(i)->Expense << "/week";
					TotalDigits = 20 - tss.str().size();
					for (int j = 0; j < TotalDigits; j++) ss << " ";
					ss << tss.str() << "\n";*/ ss << "\n";
				}

				if (Army.size() > 1) {
					ss << "\n";
					for (int i = 0; i < 1; i++) {
						int Dummy = TotalHealthy;
						if (Dummy == 0) Dummy = 1;
						int HealthyDigits = 0;
						while (Dummy > 0) {
							Dummy = Dummy / 10;
							HealthyDigits++;
						}
						int LeftOffset = 4 - HealthyDigits;

						Dummy = TotalNumber;
						int TotalDigits = 0;
						while (Dummy > 0) {
							Dummy = Dummy / 10;
							TotalDigits++;
						}
						int RightOffset = 4 - TotalDigits;

						std::stringstream tss;
						for (int j = 0; j < LeftOffset; j++) tss << " ";
						tss << TotalHealthy;
						tss << " /";
						for (int j = 0; j < RightOffset; j++) tss << " ";
						tss << TotalNumber;
						int Offset = 44 - tss.str().size();
						for (int j = 0; j < Offset; j++) ss << " ";
						ss << tss.str() << "\n";
					}

					for (int i = 0; i < 1; i++) {
						/*std::stringstream tss;
						tss << TotalCost << "/week";
						int Offset = 20 - tss.str().size();
						for (int j = 0; j < Offset; j++) ss << " ";
						ss << tss.str();*/
					}
				}

				TotalHealthy = 0;
				TotalNumber = 0;
				if (Prisoners.size() > 0) {
					ss << " -Prisoners-\n";
					for (int i = 0; i < Prisoners.size(); i++) {
						Temp = UnitType((long)Prisoners.at(i)->ID, PlayerName);
						ss << "  " << Temp;
						for (int j = 0; j < (32 - Temp.size()); j++) ss << " ";

						int Healthy = Prisoners.at(i)->Quantity - Prisoners.at(i)->Wounded;
						TotalHealthy += Healthy;
						if (Healthy == 0) Healthy++;
						int HealthyDigits = 0;
						while (Healthy > 0) {
							Healthy = Healthy / 10;
							HealthyDigits++;
						}
						int LeftOffset = 4 - HealthyDigits;
						Healthy = Prisoners.at(i)->Quantity - Prisoners.at(i)->Wounded;

						int Total = Prisoners.at(i)->Quantity;
						TotalNumber += Total;
						int TotalDigits = 0;
						while (Total > 0) {
							Total = Total / 10;
							TotalDigits++;
						}
						int RightOffset = 4 - TotalDigits;

						for (int j = 0; j < LeftOffset; j++) ss << " ";
						ss << Healthy;
						ss << " /";
						for (int j = 0; j < RightOffset; j++) ss << " ";
						ss << Prisoners.at(i)->Quantity << "\n";
					}
				}

				if (Prisoners.size() > 1) {
					ss << "\n";
					for (int i = 0; i < 1; i++) {
						int Dummy = TotalHealthy;
						if (Dummy == 0) Dummy = 1;
						int HealthyDigits = 0;
						while (Dummy > 0) {
							Dummy = Dummy / 10;
							HealthyDigits++;
						}
						int LeftOffset = 4 - HealthyDigits;

						Dummy = TotalNumber;
						int TotalDigits = 0;
						while (Dummy > 0) {
							Dummy = Dummy / 10;
							TotalDigits++;
						}
						int RightOffset = 4 - TotalDigits;

						std::stringstream tss;
						for (int j = 0; j < LeftOffset; j++) tss << " ";
						tss << TotalHealthy;
						tss << " /";
						for (int j = 0; j < RightOffset; j++) tss << " ";
						tss << TotalNumber;
						int Offset = 44 - tss.str().size();
						for (int j = 0; j < Offset; j++) ss << " ";
						ss << tss.str() << "\n";
					}
				}

				ss << "\n\n";

			}
		}
	}
	ss << "VILLAGES\n\n\n";
	//VILLAGES START HERE
	for (int z = 15; z < 21; z++) {
		for (int q = 1 + Towns + Castles; q < 1 + Towns + Castles + Villages; q++) {
			if (Data.at(q)->OriginalFaction == z && Data.at(q)->Lord == 0) {
				ss << "--" << Data.at(q)->Name << "--\n";
				ss << "  " << FactionDecoder(Data.at(q)->Faction, PlayerFaction) << "\n";
				ss << "  " << UnitType(Data.at(q)->Lord, PlayerName) << "\n\n";
				ss << "  " << "Relation                              " << Data.at(q)->Relation << "\n";
				ss << "  " << "Prosperity                            " << Data.at(q)->Prosperity << "\n\n";
				ss << "  " << "Manor                                 ";
				if (Data.at(q)->Manor) ss << "Yes\n";
				else if (Data.at(q)->CurrentImp == 130) ss << "Building, " << (Data.at(q)->ImpEndHour - Time) / 24 << " days\n";
				else ss << "No\n";

				ss << "  " << "Mill                                  ";
				if (Data.at(q)->Mill) ss << "Yes\n";
				else if (Data.at(q)->CurrentImp == 131) ss << "Building, " << (Data.at(q)->ImpEndHour - Time) / 24 << " days\n";
				else ss << "No\n";

				ss << "  " << "Watch Tower                           ";
				if (Data.at(q)->WatchT) ss << "Yes\n";
				else if (Data.at(q)->CurrentImp == 132) ss << "Building, " << (Data.at(q)->ImpEndHour - Time) / 24 << " days\n";
				else ss << "No\n";

				ss << "  " << "School                                ";
				if (Data.at(q)->School) ss << "Yes\n";
				else if (Data.at(q)->CurrentImp == 133) ss << "Building, " << (Data.at(q)->ImpEndHour - Time) / 24 << " days\n";
				else ss << "No\n";

				ss << "  " << "Messenger Post                        ";
				if (Data.at(q)->Messenger) ss << "Yes\n";
				else if (Data.at(q)->CurrentImp == 134) ss << "Building, " << (Data.at(q)->ImpEndHour - Time) / 24 << " days\n";
				else ss << "No\n";
				ss << "\n\n";
			}
		}
	}
	while (1) {
		std::cout << "Write to console or file? 0 - console, 1 - file, 2 - both\n";
		std::string Input;
		std::getline(std::cin, Input);
		if (Input == "0") {
			std::cout << ss.str();
			break;
		}
		else if (Input == "1") {
			std::ofstream os = std::ofstream("out.txt");
			std::string out = ss.str();
			
			os.write(out.c_str(), ss.str().size());
			break;
		}
		else if (Input == "2") {
			std::cout << ss.str();

			std::ofstream os;
			os.open("out.txt");
			std::string out = ss.str();

			const char* outc = out.c_str();

			os.write(outc, strlen(outc));

			os.close();
			break;
		}
		else {
			std::cout << "Invalid\n";
			continue;
		}
	}
}

bool Prompt(std::vector<Place*>& Data) {
	std::string Input;

	std::cout << "Enter blank to repeat; type to quit\n";
	std::getline(std::cin, Input);

	int j = Data.size();
	for (int i = j - 1; i >= 0; i--) {
		delete Data.at(i);
		Data.pop_back();
	}

	if (Input == "") return true;
	else return false;
}

int main() {
	std::string FilePath = "";

	Initialize(FilePath);

	while (1) {
		std::string Content = "";
		std::vector<Place*> Data;
		unsigned long Time;
		int Towns;
		int Castles;
		int Villages;
		std::string PlayerName = "";
		std::string PlayerFaction = "";

		Content = ReadFile(FilePath);
		if (Content == "") return 1;

		Data = Parse(Content, Time, Towns, Castles, Villages, PlayerName, PlayerFaction);

		PrintData(Data, Time, Towns, Castles, Villages, PlayerName, PlayerFaction);

		if (!Prompt(Data)) break;
	}

	return 0;
}