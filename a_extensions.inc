// - - - - - - - - : datas


// (C) Copyright by yPontes (R)

// @include      : a_extensions
// @version      : ( 1 )
// @infoV        : ( 1.19.41.0 ) : discriminator.define(s).function(s).codchange(s) - note: if the information from a new update is repeated in this version, discriminator(version) ++
// @github       : https://github.com/pnb-pontes
// @date         : 30th june 2025
 
// @author       : yPontes
// @contributors : Y-Hypezin, zHypezinXzL
// @sent by      : yPontes
// @codelock     : this code is open for modifications, but it is necessary to have my credits!

// @comments     : -


// - - - - - - - - : include


// custom include-guard to ensure we don't duplicate
#if (defined _yINC_a_extensions)
    // for because it is already defined in another environment
    #endinput 
#endif

// define the include (indentifier)
#define _yINC_a_extensions

// Port to open.mp and loads default variables as INVALID_PLAYER_TEXT_DRAW. (If they are using samp-stdlib)
#tryinclude <open.mp>

#if (!defined _INC_open_mp)
    #include <a_samp>
#else 
    // SAMP compatibility
	#define SAMP_COMPAT 
#endif


// - - - - - - - - : hookbacks


public OnGameModeInit (

) {
    print ("                                             ");
    print ("Loading include: a_extensions.inc            ");
    print ("                                             ");
    print ("- - - - - - - - - - :                        ");
    print ("                                             ");
    print ("   (C) Copyright by yPontes (R)              ");
    print ("                                             ");
    print ("    @include      : a_extensions             ");
    print ("    @version      : ( 1 )                    ");
    print ("    @infoV        : ( 1.19.41.0 )            ");
    print ("    @date         : 30th june 2025           ");
    print ("                                             ");
    print ("    @author       : yPontes                  ");
    print ("    @contributors : zHypezinXzL, Y-Hypezin   ");
    print ("    @sent by      : yPontes                  ");
    print ("                                             ");
    print ("- - - - - - - - - - :                        ");
    print ("                                             ");
    print (">> a_extensions included v.1 (1.19.41.0)     ");
    print ("Loaded.                                      ");
    print ("                                             ");

    #if (defined __OnGameModeInit_ext_y)
        return 
            __OnGameModeInit_ext_y (

            )
        ;
    #else 
        return 
            1
        ;
    #endif
}


// - - - - - - - - : hooks 


#if (defined _ALS_OnGameModeInit)
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit __OnGameModeInit_ext_y
#if (defined __OnGameModeInit_ext_y)
	forward __OnGameModeInit_ext_y (

    );
#endif


// - - - - - - - - : end.introduction


/*

oooooooooooo  o8o  oooo                      oooooooooooo                 .               
`888'     `8  `"'  `888                      `888'     `8               .o8               
 888         oooo   888   .ooooo.             888         oooo    ooo .o888oo             
 888oooo8    `888   888  d88' `88b            888oooo8     `88b..8P'    888               
 888    "     888   888  888ooo888            888    "       Y888'      888               
 888          888   888  888    .o            888       o  .o8"'88b     888 . .o. .o. .o. 
o888o        o888o o888o `Y8bod8P'           o888ooooood8 o88'   888o   "888" Y8P Y8P Y8P 
                                                                                          
*/


// - - - - - - - - : natives


/*

native fcreate (const file []);
native frename (const file [], const newfile []);
native fcopy (const file [], const destination [], const bool: copyifexists = true);
native fbackup (const file []);
native fclear (const file []);

native fsetstring (const file [], const string [], const bool: jumpline = false);
native fgetstring (const file [], const index);
native fgetlines (const file []);

native fkeyexist (const file [], const key []);
native fkeyrename (const file [], const key [], const newkey []);
native fkeyremove (const file [], const key []);

native fgetkeystringex (const file [], const key [], dest [], len = sizeof dest);
native fsetkeystring (const file [], const key [], const value []);
native fsetkeyinteger (const file [], const key [], const _: value);
native fsetkeyfloating (const file [], const key [], const Float: value);
native fsetkeyboolean (const file [], const key [], const bool: value);

native fgetkeystring (const file [], const key []);
native fgetkeyinteger (const file [], const key []);
native fgetkeyfloating (const file [], const key []);
native fgetkeyboolean (const file [], const key []);

*/


// - - - - - - - - : defines


// The maximum number of characters the name can contain - 64 to normal
#if !defined EXT_MAX_FILE_NAME
	#define EXT_MAX_FILE_NAME \
        ( 64 )
#endif

// The maximum number of characters that each line of the file can contain - 252 to normal
#if !defined EXT_MAX_FILE_CHARS
	#define EXT_MAX_FILE_CHARS \
        ( (252) + 3 + 1 ) // size + key separator + null
#endif


// - - - - - - - - : functions


stock fcreate (
    const file []
) {
    if (!fexist (file)) {
        new 
            File: __ext_file;
        __ext_file = fopen (file);
        if (fclose (__ext_file))
            return 1;
    }
    return 0;
}

#if (!defined frename)
	stock frename (
		const file [],
		const newfile []
	) {
		if (fexist (file)) {
			if (!fexist (newfile)) {
				if (fcopy (file, newfile)) {
					return fremove (file);
				}
			}
		}
		return 0;
	}
#endif

#if (!defined fcopy)
	stock fcopy (
		const file [], 
		const destination [], 
		const bool: copyifexists = true
	) {
		if (fexist (file)) {
			if (!copyifexists && fexist (destination)) {
				// copyifexists (false) and already exists
			} else {
				new 
					File: __ext_file;
				__ext_file = fopen (file, io_read);
				if (__ext_file) {
					new 
						File: __ext_filecopy;
					__ext_filecopy = fopen (destination, io_write);
					if (__ext_filecopy) {
						new 
							__ext_filestring [EXT_MAX_FILE_CHARS];
						while (fread (__ext_file, __ext_filestring)) {
							fwrite (__ext_filecopy, __ext_filestring);       
						}
						if (fclose (__ext_file)) {
							if (fclose (__ext_filecopy)) {
								return 1;
							}
						}
					}
				}
			}
		}
		return 0;
	}
#endif

stock fbackup (
    const file []
) {
    new 
        __ext_filebkp [EXT_MAX_FILE_NAME + 50];
    if (fexist (file)) {
        new 
            __ext_filedate [3], 
            __ext_filetime [3];
        getdate (__ext_filedate [0], __ext_filedate [1], __ext_filedate [2]);
        gettime (__ext_filetime [0], __ext_filetime [1], __ext_filetime [2]);
        format (__ext_filebkp, sizeof __ext_filebkp - 50, file);
        format (__ext_filebkp, sizeof __ext_filebkp, "%s.backup[Y(%i)-M(%i)-D(%i)-H(%i)-M(%i)-S(%i)]", __ext_filebkp, __ext_filedate [0], __ext_filedate [1], __ext_filedate [2], __ext_filetime [0], __ext_filetime [1], __ext_filetime [2]);
        if (fcopy (file, __ext_filebkp))
            return __ext_filebkp;
    }
    return __ext_filebkp;
}

stock fclear (
    const file []
) {
    if (fexist (file)) {
        new 
            File: __ext_file;
        __ext_file = fopen (file, io_write);
        if (__ext_file) {
            fwrite (__ext_file, "");
            return fclose (__ext_file);
        }
    }
    return 0;
}

stock fsetstring (
    const file [], 
    const string [],
    const bool: jumpline = false
) {
    if (fexist (file)) {
        if (strlen (string) <= EXT_MAX_FILE_CHARS) {
            new 
                File: __ext_file;
            __ext_file = fopen (file, io_read);
            if (__ext_file) {
                new 
                    File: __ext_filecopy, 
                    __ext_filestring [EXT_MAX_FILE_CHARS];
                format (__ext_filestring, sizeof __ext_filestring, "%s.forcopy_f2", file);
                if (fexist (__ext_filestring))
                    fremove (__ext_filestring);
                __ext_filecopy = fopen (__ext_filestring, io_write);
                if (__ext_filecopy) {
                    new 
                        __ext_fileindex;
                    while (fread (__ext_file, __ext_filestring)) {
                        fwrite (__ext_filecopy, __ext_filestring); 
                        __ext_fileindex ++;
                    }
                    format (__ext_filestring, sizeof __ext_filestring, string);
                    _flinekill (__ext_filestring);
                    fwrite (__ext_filecopy, __ext_filestring);
                    if (jumpline)
                        fwrite (__ext_filecopy, "\r\n");
                    if (fclose (__ext_filecopy)) {
                        if (fclose (__ext_file)) {
                            format (__ext_filestring, sizeof __ext_filestring, "%s.forcopy_f2", file);
                            if (fcopy (__ext_filestring, file)) {
                                if (fremove (__ext_filestring)) {
                                    return __ext_fileindex;
                                }
                            }
                        }
                    }
                }
            } 
        }
    }
    return -1;
}

stock fgetstring (
    const file [],
    const index
) {
    new 
        __ext_filestring [EXT_MAX_FILE_CHARS];
    if (fexist (file)) {
        new
            File: __ext_file;
        __ext_file = fopen (file, io_read);
        if (__ext_file) {
            new 
                __ext_fileindex;
            while (fread (__ext_file, __ext_filestring)) {
                if (__ext_fileindex == index) {
                    break;
                }
                __ext_fileindex ++;
            }
            if (fclose (__ext_file)) {
                return __ext_filestring;
            }
            __ext_filestring = "\0";
        }
    }
    return __ext_filestring;
}

stock fgetlines (
    const file []
) {
    if (fexist (file)) {
        new 
            File: __ext_file;
        __ext_file = fopen (file, io_read);
        if (__ext_file) {
            new 
                __ext_filestring [EXT_MAX_FILE_CHARS], 
                __ext_filekeys;
            while (fread (__ext_file, __ext_filestring)) {
                __ext_filekeys ++;
            }
            if (fclose (__ext_file)) {
                return (__ext_filekeys / 2);
            }
        }
    }
    return 0;
}

stock fkeyexist (
    const file [], 
    const key []
) {
    if (fexist (file)) {
        if (key [0] && strlen (key) <= EXT_MAX_FILE_CHARS) {
            new 
                File: __ext_file;
            __ext_file = fopen (file, io_read);
            if (__ext_file) {
                new
                    __ext_filestring [EXT_MAX_FILE_CHARS];
                while (fread (__ext_file, __ext_filestring)) {
                    if (!strcmp (__ext_filestring, key, true, strlen (key))) {
                        if (__ext_filestring [strlen (key) + 1] == '=') {
                            if (fclose (__ext_file)) {
                                return 1;
                            }
                        }
                    }
                }
                fclose (__ext_file);
            }
        }
    }
    return 0;
}

stock  fkeyrename (
    const file [],
    const key [],
    const newkey []
) {
    if (fexist (file)) {
        if (fkeyexist (file, key)) {
            new 
                File: __ext_file;
            __ext_file = fopen (file, io_read);
            if (__ext_file) {
                new 
                    File: __ext_filecopy, 
                    __ext_filestring [EXT_MAX_FILE_CHARS];
                format (__ext_filestring, sizeof __ext_filestring, "%s.forcopy_f2", file);
                if (fexist (__ext_filestring))
                    fremove (__ext_filestring);
                __ext_filecopy = fopen (__ext_filestring, io_write);
                if (__ext_filecopy) {
                    while (fread (__ext_file, __ext_filestring)) {
                        if (!strcmp (__ext_filestring, key, true, strlen (key))) {
                            if (__ext_filestring [strlen (key) + 1] == '=') { 
                                fgetkeystringex (file, key, __ext_filestring);
                                format (__ext_filestring, sizeof __ext_filestring, "%s = %s", newkey, __ext_filestring);
                                fwrite (__ext_filecopy, __ext_filestring); 
                                fwrite (__ext_filecopy, "\r\n");
                            }
                        } else {
                            _flinekill (__ext_filestring);
                            fwrite (__ext_filecopy, __ext_filestring); 
                            fwrite (__ext_filecopy, "\r\n");
                        }
                    }
                    if (fclose (__ext_filecopy)) {
                        if (fclose (__ext_file)) {
                            format (__ext_filestring, sizeof __ext_filestring, "%s.forcopy_f2", file);
                            if (fcopy (__ext_filestring, file)) {
                                if (fremove (__ext_filestring)) {
                                    return 1;
                                }
                            }
                        }
                    }
                }
                fclose (__ext_file);
            }
        }
    }
    return 0;
}

stock fkeyremove (
    const file [], 
    const key []
) {
    if (fexist (file)) {
        if (fkeyexist (file, key)) {
            new 
                File: __ext_file;
            __ext_file = fopen (file, io_read);
            if (__ext_file) {
                new 
                    File: __ext_filecopy, 
                    __ext_filestring [EXT_MAX_FILE_CHARS];
                format (__ext_filestring, sizeof __ext_filestring, "%s.forcopy_f2", file);
                if (fexist (__ext_filestring))
                    fremove (__ext_filestring);
                __ext_filecopy = fopen (__ext_filestring, io_write);
                if (__ext_filecopy) {
                    while (fread (__ext_file, __ext_filestring)) {
                        if (!strcmp (__ext_filestring, key, true, strlen (key))) {
                            if (__ext_filestring [strlen (key) + 1] == '=') { 
                                // ignore key
                            }
                        } else {
                            _flinekill (__ext_filestring);
                            fwrite (__ext_filecopy, __ext_filestring); 
                            fwrite (__ext_filecopy, "\r\n");
                        }
                    }
                    if (fclose (__ext_filecopy)) {
                        if (fclose (__ext_file)) {
                            format (__ext_filestring, sizeof __ext_filestring, "%s.forcopy_f2", file);
                            if (fcopy (__ext_filestring, file)) {
                                if (fremove (__ext_filestring)) {
                                    return 1;
                                }
                            }
                        }
                    }
                }
                fclose (__ext_file);
            }
        }
    }
    return 0;
}

stock fsetkeystring (
    const file [], 
    const key [],
    const value []
) {
    if (fexist (file)) {
        if (key [0] && value [0] && (strlen (key) + strlen (value)) <= EXT_MAX_FILE_CHARS) {
            new 
                File: __ext_file;
            __ext_file = fopen (file, io_read);
            if (__ext_file) {
                new 
                    File: __ext_filecopy, 
                    __ext_filestring [EXT_MAX_FILE_CHARS];
                format (__ext_filestring, sizeof __ext_filestring, "%s.forcopy_f2", file);
                if (fexist (__ext_filestring))
                    fremove (__ext_filestring);
                __ext_filecopy = fopen (__ext_filestring, io_write);
                if (__ext_filecopy) {
                    new 
                        bool: _fileseted = false;
                    while (fread (__ext_file, __ext_filestring)) {
                        if (!_fileseted && __ext_filestring [strlen (key) + 1] == '=' && !strcmp (__ext_filestring, key, true, strlen (key))) {
                            format (__ext_filestring, sizeof __ext_filestring, "%s = %s", key, value);
                            _fileseted = true;
                        } else
                            _flinekill (__ext_filestring);
                        fwrite (__ext_filecopy, __ext_filestring); 
                        fwrite (__ext_filecopy, "\r\n");
                    }
                    if (!_fileseted) {
                        format (__ext_filestring, sizeof __ext_filestring, "%s = %s", key, value);
                        fwrite (__ext_filecopy, __ext_filestring);
                        fwrite (__ext_filecopy, "\r\n");
                    }
                    if (fclose (__ext_filecopy)) {
                        if (fclose (__ext_file)) {
                            format (__ext_filestring, sizeof __ext_filestring, "%s.forcopy_f2", file);
                            if (fcopy (__ext_filestring, file)) {
                                return fremove (__ext_filestring);
                            }
                        }
                    }
                }
            } 
        }
    }
    return 0;
}

stock fsetkeyinteger (
    const file [], 
    const key [],
    const _: value
) {
    new
        __ext_filestring [25]; 
    valstr (__ext_filestring, value);
    return fsetkeystring (file, key, __ext_filestring);
}

stock fsetkeyfloating (
    const file [], 
    const key [],
    const Float: value
) {
    new 
        __ext_filestring [25]; 
    format (__ext_filestring, sizeof __ext_filestring, "%f", value);
    return fsetkeystring (file, key, __ext_filestring);
}

stock fsetkeyboolean (
    const file [], 
    const key [],
    const bool: value
) {
    return fsetkeystring (file, key, value ? ("true") : ("false"));
}

stock fgetkeystring (
    const file [], 
    const key []
) {
    new 
        __ext_filestring [EXT_MAX_FILE_CHARS];
    if (fexist (file)) {
        if (key [0] && strlen (key) <= EXT_MAX_FILE_CHARS) {
            if (fkeyexist (file, key)) {
                new 
                    File: __ext_file;
                __ext_file = fopen (file);
                if (__ext_file) {
                    while (fread (__ext_file, __ext_filestring))
                        if (!strcmp (__ext_filestring, key, true, strlen (key))) {
                            if (__ext_filestring [strlen (key) + 1] == '=') {
                                _flinekill (__ext_filestring);
                                strmid (__ext_filestring, __ext_filestring,  (strlen (key) + 3), strlen (__ext_filestring));
                                fclose (__ext_file);
                                return __ext_filestring;
                            }
                        }
                    fclose (__ext_file);
                    return __ext_filestring;
                } 
            }
        } 
    }
    return __ext_filestring;
}

stock fgetkeystringex (
    const file [], 
    const key [],
    dest [],
    len = sizeof dest
) {
    format (dest, len, fgetkeystring (file, key));
    return ;
}

stock _: fgetkeyinteger (
    const file [], 
    const key []
) {
    return strval (fgetkeystring (file, key)); 
}

stock Float: fgetkeyfloating (
    const file [], 
    const key []
) {
    return floatstr (fgetkeystring (file, key));
}

stock bool: fgetkeyboolean (
    const file [], 
    const key []
) {
	return (strval (fgetkeystring (file, key)) || (!strcmp (fgetkeystring (file, key), "true")));
}


// - - - - - - - - : oters


// function with purpose only to include
static stock _flinekill (
    string []
) {
    if (string [0]) {
        new
            __ext_filesize;
        __ext_filesize = strlen (string);
        if ((string [__ext_filesize - 1] == '\n') || (string [__ext_filesize - 1] == '\r')) {
            string [__ext_filesize - 1] = 0;
            if (string [0]) {
                if ((string [__ext_filesize - 2] == '\n') || (string [__ext_filesize - 2] == '\r')) {
                    string [__ext_filesize - 2] = 0;
                }
            }
        }
    }
}


// - - - - - - - - : end.file.ext


/*

  .oooooo.                            .              o8o                        oooooooooooo                 .               
 d8P'  `Y8b                         .o8              `"'                        `888'     `8               .o8               
888          oooo  oooo  oooo d8b .o888oo  .oooo.   oooo  ooo. .oo.              888         oooo    ooo .o888oo             
888          `888  `888  `888""8P   888   `P  )88b  `888  `888P"Y88b             888oooo8     `88b..8P'    888               
888           888   888   888       888    .oP"888   888   888   888             888    "       Y888'      888               
`88b    ooo   888   888   888       888 . d8(  888   888   888   888             888       o  .o8"'88b     888 . .o. .o. .o. 
 `Y8bood8P'   `V88V"V8P' d888b      "888" `Y888""8o o888o o888o o888o           o888ooooood8 o88'   888o   "888" Y8P Y8P Y8P 
                                                                                     
*/


// - - - - - - - - : natives


/*

native ShowPlayerCurtain (playerid, time, curtainid, permanence = 500);
native HidePlayerCurtain (playerid);
native IsCurtainExists (playerid);

OnPlayerUpdateCurtain (playerid, time, permanence, curtainid, bool: invert, progress)
OnPlayerCurtainClosed (playerid, curtainid)

*/


// - - - - - - - - : callbacks


forward OnPlayerUpdateCurtain (
    playerid,
    time,
    permanence,
    curtainid,
    bool: invert,
    progress
);

forward OnPlayerCurtainClosed (
    playerid,
    curtainid
);


// - - - - - - - - : defines


#if !defined INVALID_PLAYER_TEXT_DRAW
    #define INVALID_PLAYER_TEXT_DRAW (PlayerText:0xFFFF)
#endif

#if !defined INVALID_PLAYER_3DTEXT_ID
    #define INVALID_PLAYER_3DTEXT_ID (PlayerText:0xFFFF)
#endif


// - - - - - - - - : variables


static stock 
    PlayerText: __ext_cur_td_var_ [MAX_PLAYERS] [1]
;


// - - - - - - - - : functions


stock bool: IsCurtainExist(
    playerid
) {
    return 
        ((__ext_cur_td_var_ [playerid] [0] != INVALID_PLAYER_TEXT_DRAW) ? (true) : (false))
    ;
}

stock HidePlayerCurtain (
    playerid
) {
    if (IsCurtainExist (playerid)) {
        PlayerTextDrawDestroy (playerid, __ext_cur_td_var_ [playerid] [0]);
        __ext_cur_td_var_ [playerid] [0] = INVALID_PLAYER_TEXT_DRAW;
        return 
            1
        ;
    }
    return
        0
    ;
}

stock ShowPlayerCurtain (
    playerid,
    time,
    curtainid,
    permanence = 500
) {
    if (IsPlayerConnected (playerid) && !IsPlayerNPC (playerid) && time) {
        if (!IsCurtainExist (playerid)) {
            __ext_cur_td_var_ [playerid] [0] = CreatePlayerTextDraw (playerid, 316.000000, -77.000000, "_");
            PlayerTextDrawFont (playerid, __ext_cur_td_var_ [playerid] [0], 1);
            PlayerTextDrawLetterSize (playerid, __ext_cur_td_var_ [playerid] [0], 1.529166, 65.600013);
            PlayerTextDrawTextSize (playerid, __ext_cur_td_var_ [playerid] [0], 298.500000, 875.000000);
            PlayerTextDrawSetOutline (playerid, __ext_cur_td_var_ [playerid] [0], 1);
            PlayerTextDrawSetShadow (playerid, __ext_cur_td_var_ [playerid] [0], 0);
            PlayerTextDrawAlignment (playerid, __ext_cur_td_var_ [playerid] [0], 2);
            
            // adaptations for open-mp
            #if (!defined _INC_open_mp)
                PlayerTextDrawColor (playerid, __ext_cur_td_var_ [playerid] [0], -1);
                PlayerTextDrawBackgroundColor (playerid, __ext_cur_td_var_ [playerid] [0], 255);
				PlayerTextDrawBoxColor (playerid, __ext_cur_td_var_ [playerid] [0], 0);
            #else
                PlayerTextDrawColour (playerid, __ext_cur_td_var_ [playerid] [0], -1);
                PlayerTextDrawBackgroundColour (playerid, __ext_cur_td_var_ [playerid] [0], 255);
                PlayerTextDrawBoxColour (playerid, __ext_cur_td_var_ [playerid] [0], 0);
            #endif
            PlayerTextDrawUseBox (playerid, __ext_cur_td_var_ [playerid] [0], true);
            PlayerTextDrawSetProportional (playerid, __ext_cur_td_var_ [playerid] [0], true);
            PlayerTextDrawSetSelectable (playerid, __ext_cur_td_var_ [playerid] [0], false);
            PlayerTextDrawShow (playerid, __ext_cur_td_var_ [playerid] [0]);

            CallLocalFunction ("OnPlayerUpdateCurtain", "iiiiii", playerid, time, permanence, curtainid, false, 1);
            return 
                1
            ;
        }
    }
    return 
        0
    ;
}


// - - - - - - - - : hookbacks


public OnPlayerConnect (
    playerid
) {
    __ext_cur_td_var_ [playerid] [0] = INVALID_PLAYER_TEXT_DRAW;

    #if (defined __OnPlayerConnect_cur_ext)
        return 
            __OnPlayerConnect_cur_ext (
                playerid
            )
        ;
    #else 
        return 
            1
        ;
    #endif
}

public OnPlayerDisconnect (
    playerid,
    reason
) {
    HidePlayerCurtain (playerid);

    #if (defined __OnPlayerDisconnect_cur_ext)
        return 
            __OnPlayerDisconnect_cur_ext (
                playerid,
                reason
            )
        ;
    #else 
        return 
            1
        ;
    #endif
}

public OnPlayerUpdateCurtain (
    playerid,
    time,
    permanence,
    curtainid,
    bool: invert,
    progress
) {
    if (IsCurtainExist (playerid)) {
        if (invert) {
            if (!progress) {
                HidePlayerCurtain (playerid);
            } else {
                // adaptations for open-mp
                #if (!defined _INC_open_mp)
                    PlayerTextDrawBoxColor (playerid, __ext_cur_td_var_ [playerid] [0], progress);
                #else
                    PlayerTextDrawBoxColour (playerid, __ext_cur_td_var_ [playerid] [0], progress);
                #endif
                PlayerTextDrawShow (playerid, __ext_cur_td_var_ [playerid] [0]);

                // If u get `warning 239: literal array/string passed to a non-const parameter` using pawn compiler 3.10.10
                // Two options to fix it
                // 1 - Install pawn-stdlib and samp-stdlib updated (not the ones from the releases on github)
                // 2 - Go on a_samp and before the funcname[] in SetTimer(Ex) add const.              
                SetTimerEx ("OnPlayerUpdateCurtain", ((time / 2) / 255), false, "iiiiii", playerid, time, permanence, curtainid, invert, (progress - 1));
            }
        } else {
            if (progress == 256) {
                // adaptations for open-mp
                #if (!defined _INC_open_mp)
                    PlayerTextDrawBoxColor (playerid, __ext_cur_td_var_ [playerid] [0], 255);
                #else
                    PlayerTextDrawBoxColour (playerid, __ext_cur_td_var_ [playerid] [0], 255);
                #endif
                PlayerTextDrawShow (playerid, __ext_cur_td_var_ [playerid] [0]);

                // Calling just OnPlayerCurtainClosed will fail cause it REQUIRES for the user to create the public in their gamemode.
                // CallLocalFunction prevents the error: "error 004: function "OnPlayerCurtainClosed" is not implemented".
                CallLocalFunction ("OnPlayerCurtainClosed", "ii", playerid, curtainid);

                SetTimerEx ("OnPlayerUpdateCurtain", permanence, false, "iiiiii", playerid, time, permanence, curtainid, true, 254);
            } else {
                // adaptations for open-mp
                #if (!defined _INC_open_mp)
                    PlayerTextDrawBoxColor (playerid, __ext_cur_td_var_ [playerid] [0], progress);
                #else
                    PlayerTextDrawBoxColour (playerid, __ext_cur_td_var_ [playerid] [0], progress);
                #endif
                PlayerTextDrawShow (playerid, __ext_cur_td_var_ [playerid] [0]);

                SetTimerEx ("OnPlayerUpdateCurtain", ((time / 2) / 255), false, "iiiiii", playerid, time, permanence, curtainid, invert, (progress + 1));
            }
        }
    }

    #if (defined __OnPlayerUpdateCurtain_cur_ext)
        return 
            __OnPlayerUpdateCurtain_cur_ext (
                playerid,
                time,
                permanence,
                curtainid,
                invert,
                progress
            )
        ;
    #else 
        return 
            1
        ;
    #endif
}


// - - - - - - - - : hooks 


#if (defined _ALS_OnPlayerConnect)
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect __OnPlayerConnect_cur_ext
#if (defined __OnPlayerConnect_cur_ext)
	forward __OnPlayerConnect_cur_ext (
        playerid
    );
#endif


#if (defined _ALS_OnPlayerDisconnect)
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect __OnPlayerDisconnect_cur_ext
#if (defined __OnPlayerDisconnect_cur_ext)
	forward __OnPlayerDisconnect_cur_ext (
        playerid,
        reason
    );
#endif


#if (defined _ALS_OnPlayerUpdateCurtain)
    #undef OnPlayerUpdateCurtain
#else
    #define _ALS_OnPlayerUpdateCurtain
#endif
#define OnPlayerUpdateCurtain __OnPlayerUpdateCurtain_cur_ext
#if (defined __OnPlayerUpdateCurtain_cur_ext)
	forward __OnPlayerUpdateCurtain_cur_ext (
        playerid,
        time,
        permanence,
        curtainid,
        bool: invert,
        progress
    );
#endif


// - - - - - - - - : end.curtain.ext


/*

 .oooooo..o oooo         o8o                        oooooooooooo                 .               
d8P'    `Y8 `888         `"'                        `888'     `8               .o8               
Y88bo.       888  oooo  oooo  ooo. .oo.              888         oooo    ooo .o888oo             
 `"Y8888o.   888 .8P'   `888  `888P"Y88b             888oooo8     `88b..8P'    888               
     `"Y88b  888888.     888   888   888             888    "       Y888'      888               
oo     .d8P  888 `88b.   888   888   888             888       o  .o8"'88b     888 . .o. .o. .o. 
8""88888P'  o888o o888o o888o o888o o888o           o888ooooood8 o88'   888o   "888" Y8P Y8P Y8P 
                                                                                                 
*/


// - - - - - - - - : natives


/*

native IsValidSkinID (skinid)
native GetSkinName (skinid);
native GetSkinModelName (skinid);
native GetSkinSex (skinid);
native GetSkinSexName (skinid);
native GetSkinLocal (skinid);
native GetSkinLocalName (local);

*/


// - - - - - - - - : defines


#define EXT_MAX_SKINS (312) // skin 74 [N/A]
#define EXT_MAX_SKIN_MODEL_NAME (8)
#define EXT_MAX_SKIN_NAME (32)
#define EXT_MAX_SKIN_LOCALS (30)

#define EXT_SKIN_SEX_MALE 0
#define EXT_SKIN_SEX_FEMALE 1

#if (!defined EXT_SKIN_SEX_MALE_NAME)
	#define EXT_SKIN_SEX_MALE_NAME "Male"
#endif

#if (!defined EXT_SKIN_SEX_FEMALE_NAME)
	#define EXT_SKIN_SEX_FEMALE_NAME "Female"
#endif

#define EXT_SKIN_LOCAL_SA (2)
#define _EXT_SKIN_LOCAL_SA "San Andreas"

#define EXT_SKIN_LOCAL_LS (4)
#define _EXT_SKIN_LOCAL_LS "Los Santos"

#define EXT_SKIN_LOCAL_SF (8)
#define _EXT_SKIN_LOCAL_SF "San Fierro"

#define EXT_SKIN_LOCAL_LV (16)
#define _EXT_SKIN_LOCAL_LV "Las Venturas"

#define EXT_SKIN_LOCAL_GYM (32)
#define _EXT_SKIN_LOCAL_GYM "GYM"

#define EXT_SKIN_LOCAL_BEACHES (64)
#define _EXT_SKIN_LOCAL_BEACHES "Beaches"

#define EXT_SKIN_LOCAL_PIZZA_CO_ (128)
#define _EXT_SKIN_LOCAL_PIZZA_CO_ "Pizza"

#define EXT_SKIN_LOCAL_AIRPORTS (256)
#define _EXT_SKIN_LOCAL_AIRPORTS "Airports"

#define EXT_SKIN_LOCAL_CASINO (512)
#define _EXT_SKIN_LOCAL_CASINO "Casino"

#define EXT_SKIN_LOCAL_MADD_DG_MANSION (1024)
#define _EXT_SKIN_LOCAL_MADD_DG_MANSION "Madd Dogg Manssion"

#define EXT_SKIN_LOCAL_DOHERTY (2048)
#define _EXT_SKIN_LOCAL_DOHERTY "Doherty"

#define EXT_SKIN_LOCAL_AROUND_SA (4096)
#define _EXT_SKIN_LOCAL_AROUND_SA "Around San Andreas"

#define EXT_SKIN_LOCAL_MISSION (8192)
#define _EXT_SKIN_LOCAL_MISSION "Mission"

#define EXT_SKIN_LOCAL_AREA_6 (16384)
#define _EXT_SKIN_LOCAL_AREA_6 "Area 6"

#define EXT_SKIN_LOCAL_BAR (32768)
#define _EXT_SKIN_LOCAL_BAR "Bar"

#define EXT_SKIN_LOCAL_NULL (65536)
#define _EXT_SKIN_LOCAL_NULL "unknown"

#define EXT_SKIN_LOCAL_CLUCKIN_BELL (131072)
#define _EXT_SKIN_LOCAL_CLUCKIN_BELL "Cluckin' Bell"

#define EXT_SKIN_LOCAL_TATTO_SHOPS (262144)
#define _EXT_SKIN_LOCAL_TATTO_SHOPS "Tatto shops"

#define EXT_SKIN_LOCAL_BURGER_SHOT (524288)
#define _EXT_SKIN_LOCAL_BURGER_SHOT "Buger Shot"

#define EXT_SKIN_LOCAL_EL_QUEBRADOS (1048576)
#define _EXT_SKIN_LOCAL_EL_QUEBRADOS "El Quebrados"

#define EXT_SKIN_LOCAL_BLUEBERRY (2097152)
#define _EXT_SKIN_LOCAL_BLUEBERRY "Blueberry"

#define EXT_SKIN_LOCAL_CLOTHES_SHOPS (4194304)
#define _EXT_SKIN_LOCAL_CLOTHES_SHOPS "Clothes Shops"

#define EXT_SKIN_LOCAL_CUTSCENE (8388608)
#define _EXT_SKIN_LOCAL_CUTSCENE "Cutscene"

#define EXT_SKIN_LOCAL_NOODLE_STANDS (16777216)
#define _EXT_SKIN_LOCAL_NOODLE_STANDS "Noodle Stands"

#define EXT_SKIN_LOCAL_BOATING_SCHOOL (33554432)
#define _EXT_SKIN_LOCAL_BOATING_SCHOOL "Boating School"

#define EXT_SKIN_LOCAL_HOTDOG_VANS (67108864)
#define _EXT_SKIN_LOCAL_HOTDOG_VANS "Hotdog vans"

#define EXT_SKIN_LOCAL_DESERT (134217728)
#define _EXT_SKIN_LOCAL_DESERT "Desert"

#define EXT_SKIN_LOCAL_COUNTRY (268435456) 
#define _EXT_SKIN_LOCAL_COUNTRY "Country"

#define EXT_SKIN_LOCAL_FERN_RIDGE (536870912)
#define _EXT_SKIN_LOCAL_FERN_RIDGE "Fern Ridge"

#define EXT_SKIN_LOCAL_AMMUNATION (1073741824)
#define _EXT_SKIN_LOCAL_AMMUNATION "Ammunation"


// - - - - - - - - : variables


enum __ext_skin_info_enum {
    __ext_skin_model_name [EXT_MAX_SKIN_MODEL_NAME char],
    __ext_skin_name [EXT_MAX_SKIN_NAME char],
    __ext_skin_data [2]
};

static stock const __ext_skin_info_var [] [__ext_skin_info_enum] = {
    {!"cj", !"CJ", {EXT_SKIN_LOCAL_NULL, EXT_SKIN_SEX_MALE}},
    {!"truth", !"Truth", {EXT_SKIN_LOCAL_SF | EXT_SKIN_LOCAL_LV, EXT_SKIN_SEX_MALE}},
    {!"maccer", !"Maccer", {EXT_SKIN_LOCAL_LS | EXT_SKIN_LOCAL_LV, EXT_SKIN_SEX_MALE}},
    {!"andre", !"Andre", {EXT_SKIN_LOCAL_NULL, EXT_SKIN_SEX_MALE}},
    {!"bbthin", !"Big Bear [Thin]", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"bb", !"Big Bear [Big]", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"emmet", !"Emmet", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"male01", !"Casual JeanJacket", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"janitor", !"Janitor", {EXT_SKIN_LOCAL_CASINO, EXT_SKIN_SEX_MALE}},
    {!"bfori", !"Business Lady", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"bfost", !"Old Fat Lady", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"vbfycrp", !"Casino croupier", {EXT_SKIN_LOCAL_CASINO, EXT_SKIN_SEX_FEMALE}},
    {!"bfyri", !"Rich Woman", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"bfyst", !"Street Girl", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"bmori", !"Floral Shirt", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"bmost", !"Mr.Whittaker", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"bmyap", !"Earmuff Worker", {EXT_SKIN_LOCAL_AIRPORTS, EXT_SKIN_SEX_MALE}},
    {!"bmybu", !"Businessman", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"bmybe", !"Beach Visitor", {EXT_SKIN_LOCAL_BEACHES | EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"bmydj", !"DJ", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"bmyri", !"Rich Guy", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"bmycr", !"Striped Gangsta", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"bmyst", !"Orange Sportsman", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wmybmx", !"BMXer", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"wbdyg1", !"LS Coach", {EXT_SKIN_LOCAL_MADD_DG_MANSION, EXT_SKIN_SEX_MALE}},
    {!"wbdyg2", !"Varsity jacket", {EXT_SKIN_LOCAL_MADD_DG_MANSION, EXT_SKIN_SEX_MALE}},
    {!"wmybp", !"Backpacker", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wmycon", !"Construction Worker", {EXT_SKIN_LOCAL_DOHERTY, EXT_SKIN_SEX_MALE}},
    {!"bmydrug", !"Black Drug Dealer", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"wmydrug", !"Withe Drug Dealer", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"hmydrug", !"Vagos Drug Dealer", {EXT_SKIN_LOCAL_LV, EXT_SKIN_SEX_MALE}},
    {!"dwfolc", !"Fat Cowgirl", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"dwmolc1", !"Eyepatch", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"dwmolc2", !"Bounty Hunter", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"dwmylc1", !"Marlboro Man", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"hmogar", !"Gardener", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wmygol1", !"Golfer", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wmygol2", !"Golfer", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"hfori", !"Old Golf Lady", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"hfost", !"Old Maid", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"hfyri", !"Classy Dark Hooker", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"hfyst", !"Tracksuit Girl", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"jethro", !"Jethro", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"hmori", !"Porn Producer", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"hmost", !"Tatooed Plaid", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"hmybe", !"Beach Visitor", {EXT_SKIN_LOCAL_BEACHES | EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"hmyri", !"Dark Romeo", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"hmycr", !"boy glasses", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"hmyst", !"boy glasses 2", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"omokung", !"Snakehead", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wmymech", !"Mechanic", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"bmymoun", !"Mountain Biker Yellow", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wmymoun", !"Mountain Biker Red", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"ofori", !"Unknown", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"ofost", !"Hispanic Woman", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"ofyri", !"Rich Bitch", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"ofyst", !"Legwarmers 1", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"omori", !"Oriental Suit", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"omost", !"Oriental shirt Red", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"omyri", !"Oriental striped suit", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"omyst", !"Oriental shirt White", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wmyplt", !"Pilot", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wmopj", !"Colonel Fuhrberger", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"bfypro", !"Prostitute", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"hfypro", !"Prostitute 2", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"kendl", !"Kendl Johnson", {EXT_SKIN_LOCAL_LS | EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_FEMALE}},
    {!"bmypol1", !"Pool Player", {EXT_SKIN_LOCAL_BAR, EXT_SKIN_SEX_MALE}},
    {!"bmypol2", !"Pool Player 2", {EXT_SKIN_LOCAL_BAR | EXT_SKIN_LOCAL_NULL, EXT_SKIN_SEX_MALE}},
    {!"wmoprea", !"Priest", {EXT_SKIN_LOCAL_LV, EXT_SKIN_SEX_MALE}},
    {!"sbfyst", !"Denim Girl", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"wmosci", !"Scientist", {EXT_SKIN_LOCAL_AREA_6, EXT_SKIN_SEX_MALE}},
    {!"wmysgrd", !"Security Guard", {EXT_SKIN_LOCAL_AIRPORTS, EXT_SKIN_SEX_MALE}},
    {!"swmyhp1", !"Hippy", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"swmyhp2", !"Hippy 2", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"unknown", !"N/A", {EXT_SKIN_LOCAL_NULL, -1}},
    {!"swfopro", !"Prostitute 3", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"wfystew", !"Stewardess", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"swmotr1", !"Homeless", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"wmotr1", !"Homeless 2", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"bmotr1", !"Homeless 3", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"vbmybox", !"Boxer", {EXT_SKIN_LOCAL_SA | EXT_SKIN_LOCAL_GYM, EXT_SKIN_SEX_MALE}},
    {!"vwmybox", !"Boxer 2", {EXT_SKIN_LOCAL_SA | EXT_SKIN_LOCAL_GYM, EXT_SKIN_SEX_MALE}},
    {!"vhmyelv", !"Black Elvis", {EXT_SKIN_LOCAL_LV, EXT_SKIN_SEX_MALE}},
    {!"vbmyelv", !"White Elvis", {EXT_SKIN_LOCAL_LV, EXT_SKIN_SEX_MALE}},
    {!"vimyelv", !"Blue Elvis", {EXT_SKIN_LOCAL_LV, EXT_SKIN_SEX_MALE}},
    {!"vwfypro", !"Prostitute 4", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"ryder", !"Ryder with robbery mask", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"vwfyst1", !"Stripper", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"wfori", !"Casual Old Lady", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"wfost", !"Cleaning Lady", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"wfyjg", !"Jogger", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"wfyri", !"Rich Woman", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"wfyro", !"Rollerskater", {EXT_SKIN_LOCAL_BEACHES | EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"wfyst", !"Hoop Earrings 1", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"wmori", !"Andy Capp", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wmost", !"Jacker Hippie", {EXT_SKIN_LOCAL_SA | EXT_SKIN_LOCAL_NULL, EXT_SKIN_SEX_MALE}},
    {!"wmyjg", !"Jogger", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wmylg", !"Lifeguard", {EXT_SKIN_LOCAL_BEACHES, EXT_SKIN_SEX_MALE}},
    {!"wmyri", !"Baywatch Dude", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wmyro", !"Rollerskater", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wmycr", !"Biker", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wmyst", !"Jacker Hippie", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"ballas1", !"Balla", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"ballas2", !"Balla 2", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"ballas", !"Balla 3", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"fam1", !"Grove Street Families", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"fam2", !"Grove Street Families 2", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"fam", !"Grove Street Families 3", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"lsv1", !"Los Santos Vagos", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"lsv2", !"Los Santos Vagos 2", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"lsv", !"Los Santos Vagos 3", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"maffa", !"The Russian Mafia", {EXT_SKIN_LOCAL_AROUND_SA, EXT_SKIN_SEX_MALE}},
    {!"maffb", !"The Russian Mafia 2", {EXT_SKIN_LOCAL_AROUND_SA, EXT_SKIN_SEX_MALE}},
    {!"mafboss", !"The Russian Mafia 3", {EXT_SKIN_LOCAL_AROUND_SA, EXT_SKIN_SEX_MALE}},
    {!"vla1", !"Varios Los Aztecas", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"vla2", !"Varios Los Aztecas 2", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"vla", !"Varios Los Aztecas 3", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"triada", !"Triad", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"triadb", !"Triad 2", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"sindaco", !"Johhny Sindacco", {EXT_SKIN_LOCAL_LV, EXT_SKIN_SEX_MALE}},
    {!"triboss", !"Triad Boss", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"dnb1", !"Da Nang Boy", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"dnb2", !"Da Nang Boy 2", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"dnb", !"Da Nang Boy 3", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"vmaff1", !"The Mafia", {EXT_SKIN_LOCAL_LV, EXT_SKIN_SEX_MALE}},
    {!"vmaff2", !"The Mafia 2", {EXT_SKIN_LOCAL_LV, EXT_SKIN_SEX_MALE}},
    {!"vmaff", !"The Mafia 3", {EXT_SKIN_LOCAL_LV, EXT_SKIN_SEX_MALE}},
    {!"vmaff", !"The Mafia 4", {EXT_SKIN_LOCAL_LV, EXT_SKIN_SEX_MALE}},
    {!"dnmylc", !"Farm Inhabitant", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"dnfolc1", !"Farm Inhabitant 2", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"dnfolc2", !"Farm Inhabitant 3", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"dnfylc", !"Farm Inhabitant 4", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"dnmolc1", !"Farm Inhabitant 5", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"dnmolc2", !"Farm Inhabitant 6", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"sbmotr2", !"Homeless 4", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"swmotr2", !"Homeless 5", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"sbmytr", !"Old Rasta", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"swmotr", !"Homeless 6", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wfybe", !"Beach Visitor", {EXT_SKIN_LOCAL_BEACHES | EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"bfybe", !"Beach Visitor 2", {EXT_SKIN_LOCAL_BEACHES | EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"hfybe", !"Beach Visitor 3", {EXT_SKIN_LOCAL_BEACHES | EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"sofybu", !"Businesswoman", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"sbmyst", !"Taxi Driver", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"sbmycr", !"Crack Maker", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"bmycg", !"Crack Maker 2", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wfycrk", !"Crack Maker 3", {EXT_SKIN_LOCAL_BEACHES | EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"hmycm", !"Crack Maker 4", {EXT_SKIN_LOCAL_BEACHES | EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wmybu", !"Businessman 2", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"bfybu", !"Businesswoman 2", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"smokev", !"Big Smoke Armored", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"wfybu", !"Businesswoman 3", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"dwfylc1", !"Melanie", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"wfypro", !"Prostitute 5", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"wmyconb", !"Construction Worker", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wmybe", !"Beach Visitor", {EXT_SKIN_LOCAL_BEACHES | EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wmypizz", !"Pizza Worker", {EXT_SKIN_LOCAL_PIZZA_CO_, EXT_SKIN_SEX_MALE}},
    {!"bmobar", !"Barber", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"cwfyhb", !"Hillbilly", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"cwmofr", !"Farmer", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"cwmohb1", !"Hillbilly 2", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"cwmohb2", !"Hillbilly 3", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"cwmyfr", !"Farmer 2", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"cwmyhb1", !"Hillbilly 4", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"bmyboun", !"Black Bouncer", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wmyboun", !"White Bouncer", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wmomib", !"White MIB agent", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"bmymib", !"Black MIB agent", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wmybell", !"Cluckin' Bell Worker", {EXT_SKIN_LOCAL_CLUCKIN_BELL, EXT_SKIN_SEX_MALE}},
    {!"bmochil", !"Hotdog", {EXT_SKIN_LOCAL_HOTDOG_VANS, EXT_SKIN_SEX_MALE}},
    {!"sofyri", !"Asian Escort", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"somyst", !"PubeStache Tshirt", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"vwmybjd", !"Blackjack Dealer", {EXT_SKIN_LOCAL_CASINO, EXT_SKIN_SEX_MALE}},
    {!"vwfycrp", !"Casino croupier", {EXT_SKIN_LOCAL_CASINO, EXT_SKIN_SEX_FEMALE}},
    {!"sfr1", !"San Fierro Rifa", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"sfr2", !"San Fierro Rifa", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"sfr", !"San Fierro Rifa", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"bmybar", !"Barber", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wmybar", !"Barber", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wfysex", !"Whore", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"wmyammo", !"Ammunation Salesman", {EXT_SKIN_LOCAL_AMMUNATION, EXT_SKIN_SEX_MALE}},
    {!"bmytatt", !"Tattoo Artist", {EXT_SKIN_LOCAL_TATTO_SHOPS, EXT_SKIN_SEX_MALE}},
    {!"vwmycr", !"Punk", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"vbmocd", !"Cab Driver", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"vbmycr", !"Klingon", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"vhmycr", !"Neckbeard", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"sbmyri", !"Nervous Guy", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"somyri", !"Teacher", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"somybu", !"Businessman 3", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"swmyst", !"Green Shirt", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wmyva", !"Valet", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"copgrl", !"Barbara Schternvart", {EXT_SKIN_LOCAL_EL_QUEBRADOS, EXT_SKIN_SEX_FEMALE}},
    {!"gungrl", !"Helena Wankstein", {EXT_SKIN_LOCAL_BLUEBERRY, EXT_SKIN_SEX_FEMALE}},
    {!"mecgrl", !"Michelle Cannes", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_FEMALE}},
    {!"nurgrl", !"Katie Zhan", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_FEMALE}},
    {!"crogrl", !"Millie Perkins", {EXT_SKIN_LOCAL_LV, EXT_SKIN_SEX_FEMALE}},
    {!"gangrl", !"Denise Robinson", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_FEMALE}},
    {!"cwfofr", !"Farm-Town inhabitant", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"cwfohb", !"Hillbilly 5", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"cwfyfr1", !"Farm-Town inhabitant 2", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"cwfyfr2", !"Farm-Town inhabitant 3", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"cwmyhb2", !"Hillbilly 6", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"dwfylc2", !"Farmer 3", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"dwmylc2", !"Farmer 4", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"omykara", !"Karate Teacher", {EXT_SKIN_LOCAL_SF | EXT_SKIN_LOCAL_GYM, EXT_SKIN_SEX_MALE}},
    {!"wmykara", !"Karate Teacher 2", {EXT_SKIN_LOCAL_SF | EXT_SKIN_LOCAL_GYM, EXT_SKIN_SEX_MALE}},
    {!"wfyburg", !"Burger Shot Cashier", {EXT_SKIN_LOCAL_BURGER_SHOT, EXT_SKIN_SEX_FEMALE}},
    {!"vwmycd", !"Cab Driver", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"vhfypro", !"Prostitute 6", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"suzie", !"Su Xi Mu", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"omonood", !"Noodle stand vendor", {EXT_SKIN_LOCAL_NOODLE_STANDS, EXT_SKIN_SEX_MALE}},
    {!"omoboat", !"Boating School Instructor", {EXT_SKIN_LOCAL_BOATING_SCHOOL, EXT_SKIN_SEX_MALE}},
    {!"wfyclot", !"Clothes shop staff", {EXT_SKIN_LOCAL_CLOTHES_SHOPS, EXT_SKIN_SEX_FEMALE}},
    {!"vwmotr1", !"Homeless", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"vwmotr2", !"Weird old man", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"vwfywai", !"Maria Latore", {EXT_SKIN_LOCAL_CUTSCENE | EXT_SKIN_LOCAL_CASINO, EXT_SKIN_SEX_FEMALE}},
    {!"sbfori", !"Explorer", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"swfyri", !"Turtleneck", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"wmyclot", !"Clothes shop staff", {EXT_SKIN_LOCAL_CLOTHES_SHOPS, EXT_SKIN_SEX_MALE}},
    {!"sbfost", !"Old Woman", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"sbfyri", !"Rich Woman", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"sbmocd", !"Cab Driver", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"sbmori", !"Beardo Casual", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"sbmost", !"Beardo Clubbing", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"shmycr", !"Greasy Nightclubber", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"sofori", !"Elderly Asian 1", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"sofost", !"Elderly Asian 2", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"sofyst", !"Legwarmers 2", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"somobu", !"Oriental Businessman", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"somori", !"Oriental Ped", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"somost", !"Oriental Ped", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"swmotr", !"Homeless", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"swfori", !"Grannie", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"swfost", !"Grouchy lady", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"swfyst", !"Hoop Earrings 2", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"swmocd", !"Cab Driver", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"swmori", !"Retired Tourist", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"swmost", !"Happy Old Man", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"shfypro", !"Prostitute 7", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"sbfypro", !"Prostitute 8", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"swmotr", !"Homeless", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"swmyri", !"The D.A", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"smyst", !"Afro-American", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"smyst2", !"Mexican", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"sfypro", !"Prostitute 9", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"vbfyst2", !"Stripper", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"vbfypro", !"Prostitute 10", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"vhfyst", !"Stripper", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"bikera", !"Biker", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"bikerb", !"Biker", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"bmypimp", !"Pimp", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"swmycr", !"Green Tshirt", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wfylg", !"Lifeguard", {EXT_SKIN_LOCAL_BEACHES, EXT_SKIN_SEX_FEMALE}},
    {!"wmyva2", !"Naked Valet", {EXT_SKIN_LOCAL_MISSION | EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"bmosec", !"Bus Driver", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"bikdrug", !"Biker Drug Dealer", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"wmych", !"Chauffeur", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"sbfystr", !"Stripper", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"swfystr", !"Stripper", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"heck1", !"Heckler", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"heck2", !"Heckler", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"bmycon", !"Construction Worker", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"wmycd1", !"Cab driver", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"bmocd", !"Cab driver", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"vwfywa2", !"Asian Hostess", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_FEMALE}},
    {!"wmoice", !"Clown", {EXT_SKIN_LOCAL_SA | EXT_SKIN_LOCAL_NULL, EXT_SKIN_SEX_MALE}},
    {!"tenpen", !"Frank Tenpenny", {EXT_SKIN_LOCAL_MISSION, EXT_SKIN_SEX_MALE}},
    {!"pulaski", !"Eddie Pulaski", {EXT_SKIN_LOCAL_MISSION, EXT_SKIN_SEX_MALE}},
    {!"hern", !"Jimmy Hernandez", {EXT_SKIN_LOCAL_MISSION, EXT_SKIN_SEX_MALE}},
    {!"dwayne", !"Dwayne", {EXT_SKIN_LOCAL_SF | EXT_SKIN_LOCAL_MISSION, EXT_SKIN_SEX_MALE}},
    {!"smoke", !"Big Smoke", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"sweet", !"Sweet", {EXT_SKIN_LOCAL_LS | EXT_SKIN_LOCAL_SF | EXT_SKIN_LOCAL_MISSION, EXT_SKIN_SEX_MALE}},
    {!"ryder", !"Ryder", {EXT_SKIN_LOCAL_LS | EXT_SKIN_LOCAL_SF | EXT_SKIN_LOCAL_MISSION, EXT_SKIN_SEX_MALE}},
    {!"forelli", !"Mafia Boss", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"tbone", !"T-Bone Mendez", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"laemt1", !"Paramedic", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"lvemt1", !"Paramedic 2", {EXT_SKIN_LOCAL_LV, EXT_SKIN_SEX_MALE}},
    {!"sfemt1", !"Paramedic 3", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"lafd1", !"Firefighter", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"lvfd1", !"Firefighter 2", {EXT_SKIN_LOCAL_LV, EXT_SKIN_SEX_MALE}},
    {!"sffd1", !"Firefighter 3", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"lapd1", !"LS Police Officer", {EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"sfpd1", !"SF Police Officer", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"lvpd1", !"LV Police Officer", {EXT_SKIN_LOCAL_LV, EXT_SKIN_SEX_MALE}},
    {!"csher", !"County Sheriff", {EXT_SKIN_LOCAL_COUNTRY, EXT_SKIN_SEX_MALE}},
    {!"lapdm1", !"LSPD Motorbike Cop", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"swat", !"S.W.A.T Special Forces", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"fbi", !"FBI Agent", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"army", !"SA Army Soldier", {EXT_SKIN_LOCAL_SA, EXT_SKIN_SEX_MALE}},
    {!"dsher", !"Desert Sheriff", {EXT_SKIN_LOCAL_DESERT, EXT_SKIN_SEX_MALE}},
    {!"zero", !"Zero", {EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"rose", !"Ken Rosenberg", {EXT_SKIN_LOCAL_MADD_DG_MANSION, EXT_SKIN_SEX_MALE}},
    {!"paul", !"Kent Paul", {EXT_SKIN_LOCAL_LV | EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"cesar", !"Cesar Vialpando", {EXT_SKIN_LOCAL_LS | EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"ogloc", !"OG Loc", {EXT_SKIN_LOCAL_LS | EXT_SKIN_LOCAL_BURGER_SHOT, EXT_SKIN_SEX_MALE}},
    {!"wuzimu", !"Wu Zi Mu", {EXT_SKIN_LOCAL_SF | EXT_SKIN_LOCAL_LV, EXT_SKIN_SEX_MALE}},
    {!"torino", !"Michael Toreno", {EXT_SKIN_LOCAL_LV | EXT_SKIN_LOCAL_SF, EXT_SKIN_SEX_MALE}},
    {!"jizzy", !"Jizzy B.", {EXT_SKIN_LOCAL_SF | EXT_SKIN_LOCAL_NULL, EXT_SKIN_SEX_MALE}},
    {!"maddogg", !"Madd Dogg", {EXT_SKIN_LOCAL_MADD_DG_MANSION | EXT_SKIN_LOCAL_LS, EXT_SKIN_SEX_MALE}},
    {!"cat", !"Catalina", {EXT_SKIN_LOCAL_FERN_RIDGE, EXT_SKIN_SEX_FEMALE}},
    {!"claude", !"Claude Speed", {EXT_SKIN_LOCAL_CUTSCENE, EXT_SKIN_SEX_MALE}},

    // WARNING
    // These skins (300 to 311) were added in SA-MP 0.3.7 RC3 and will not work in earlier versions!
    {!"lapdna", !"LS Police gun holster", {EXT_SKIN_LOCAL_NULL, EXT_SKIN_SEX_MALE}},
    {!"sfpdna", !"SF Police gun holster", {EXT_SKIN_LOCAL_NULL, EXT_SKIN_SEX_MALE}},
    {!"lvpdna", !"LV Police gun holster", {EXT_SKIN_LOCAL_NULL, EXT_SKIN_SEX_MALE}},
    {!"lapdpc", !"LS Police uniform", {EXT_SKIN_LOCAL_NULL, EXT_SKIN_SEX_MALE}},
    {!"lapdpd", !"LS Police uniform", {EXT_SKIN_LOCAL_NULL, EXT_SKIN_SEX_MALE}},
    {!"lvpdpc", !"LV Police uniform", {EXT_SKIN_LOCAL_NULL, EXT_SKIN_SEX_MALE}},
    {!"wfyclpd", !"LS Police", {EXT_SKIN_LOCAL_NULL, EXT_SKIN_SEX_FEMALE}},
    {!"vbfycpd", !"SF Police", {EXT_SKIN_LOCAL_NULL, EXT_SKIN_SEX_FEMALE}},
    {!"wfyclem", !"SF Paramedic", {EXT_SKIN_LOCAL_NULL, EXT_SKIN_SEX_FEMALE}},
    {!"wfycllv", !"LV Police", {EXT_SKIN_LOCAL_NULL, EXT_SKIN_SEX_FEMALE}},
    {!"csherna", !"Country Sheriff", {EXT_SKIN_LOCAL_NULL, EXT_SKIN_SEX_MALE}},
    {!"dsherna", !"Desert Sheriff", {EXT_SKIN_LOCAL_NULL, EXT_SKIN_SEX_MALE}}
};



// - - - - - - - - : functions

stock bool: IsValidSkinID (
    skinid
) {
    switch (skinid) {
        case 0..73, 75..311: {
            return 
                true
            ;            
        }
    }
    return 
        false
    ;
}

stock GetSkinModelName (
    skinid
) {
    static 
        __ext_skin_string [EXT_MAX_SKIN_MODEL_NAME] = "\0"
    ;
    __ext_skin_string = "unknown";
    if (IsValidSkinID (skinid))
        strunpack (__ext_skin_string, __ext_skin_info_var [skinid] [__ext_skin_model_name], EXT_MAX_SKIN_MODEL_NAME);
    return 
        __ext_skin_string
    ;
}

stock GetSkinName (
    skinid
) {
    static 
        __ext_skin_string [EXT_MAX_SKIN_NAME] = "\0"
    ;
    __ext_skin_string = "N/A";
    if (IsValidSkinID (skinid)) 
        strunpack (__ext_skin_string, __ext_skin_info_var [skinid] [__ext_skin_name], EXT_MAX_SKIN_NAME);    
    return 
        __ext_skin_string
    ;
}

stock GetSkinSex (
    skinid
) {
    return
        (IsValidSkinID (skinid)) ? (__ext_skin_info_var [skinid] [__ext_skin_data] [1]) : (-1)
    ;
}

stock GetSkinSexName (
    skinid
) {
    static 
        __ext_skin_string [EXT_MAX_SKIN_NAME] = "\0"
    ;
    __ext_skin_string = "N/A";
    if (IsValidSkinID (skinid)) 
		format (__ext_skin_string, EXT_MAX_SKIN_NAME, (__ext_skin_info_var [skinid] [__ext_skin_data] [1] ? EXT_SKIN_SEX_MALE_NAME : EXT_SKIN_SEX_FEMALE_NAME));   
    return 
        __ext_skin_string
    ;
}

stock GetSkinLocal (
    skinid
) {
    return
        (IsValidSkinID (skinid)) ? (__ext_skin_info_var [skinid] [__ext_skin_data] [0]) : (EXT_SKIN_LOCAL_NULL)
    ;
}

stock GetSkinLocalName (
    local
) {
    static 
        __ext_skin_string [128],
        bool: __ext_skin_already
    ; 
    __ext_skin_string = "\0";
    __ext_skin_already = false;

    if (local & EXT_SKIN_LOCAL_FERN_RIDGE) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_FERN_RIDGE);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_COUNTRY) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_COUNTRY);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_DESERT) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_DESERT);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_HOTDOG_VANS) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_HOTDOG_VANS);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_BOATING_SCHOOL) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_BOATING_SCHOOL);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_NOODLE_STANDS) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_NOODLE_STANDS);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_CUTSCENE) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_CUTSCENE);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_CLOTHES_SHOPS) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_CLOTHES_SHOPS);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_BLUEBERRY) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_BLUEBERRY);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_EL_QUEBRADOS) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_EL_QUEBRADOS);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_BURGER_SHOT) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_BURGER_SHOT);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_TATTO_SHOPS) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_TATTO_SHOPS);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_CLUCKIN_BELL) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_CLUCKIN_BELL);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_AMMUNATION) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_AMMUNATION);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_BAR) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_BAR);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_AREA_6) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_AREA_6);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_MISSION) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_MISSION);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_AROUND_SA) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_AROUND_SA);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_DOHERTY) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_DOHERTY);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_MADD_DG_MANSION) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_MADD_DG_MANSION);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_CASINO) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_CASINO);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_AIRPORTS) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_AIRPORTS);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_PIZZA_CO_) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_PIZZA_CO_);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_BEACHES) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_BEACHES);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_GYM) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_GYM);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_LV) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_LV);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_SF) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_SF);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_LS) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_LS);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_SA) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_SA);
        __ext_skin_already = true;
    }
    if (local & EXT_SKIN_LOCAL_NULL) {
        if (__ext_skin_already)
            strcat (__ext_skin_string, ", ");
        strcat (__ext_skin_string, _EXT_SKIN_LOCAL_NULL);
    }
    return
        __ext_skin_string
    ;
}


// - - - - - - - - : end.skin.ext


/*

  .o     o    ooooooooo.                                                               oooooooooooo                 .               
o888  `8.8.8' `888   `Y88.                                                             `888'     `8               .o8               
 888  .8'8`8.  888   .d88'  .ooooo.  oooo d8b  .oooo.o  .ooooo.  ooo. .oo.              888         oooo    ooo .o888oo             
 888     "     888ooo88P'  d88' `88b `888""8P d88(  "8 d88' `88b `888P"Y88b             888oooo8     `88b..8P'    888               
 888           888         888ooo888  888     `"Y88b.  888   888  888   888             888    "       Y888'      888               
 888           888         888    .o  888     o.  )88b 888   888  888   888             888       o  .o8"'88b     888 . .o. .o. .o. 
o888o         o888o        `Y8bod8P' d888b    8""888P' `Y8bod8P' o888o o888o           o888ooooood8 o88'   888o   "888" Y8P Y8P Y8P 
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
*/


// - - - - - - - - : natives


/*

native ResetCamPosFirstPersonPlayer (playerid);
native SetCamPositionFirstPersonPlayer (Float: position, type = EXT_FC_FOOT_TYPE, mode = EXT_FC_FRONT_MODE);

native SetCamFirstPersonPlayer (playerid, bool: use_in_veh = true);
native CancelCamFirstPersonPlayer (playerid, bool: cam_behind = true);
native IsCamFirstPersonPlayer (playerid);

*/


// - - - - - - - - : defines


#if (!defined INC_FC_OBJECT_CAM)
	#define INC_FC_OBJECT_CAM 19300
#endif


#define EXT_FC_FOOT_TYPE 0
#define EXT_FC_SWIM_TYPE 1
#define EXT_FC_CROUCH_TYPE 2
#define EXT_FC_VEH_TYPE 3 
#define EXT_FC_AIM_TYPE 4

#define EXT_FC_FRONT_MODE 0
#define EXT_FC_HEIGHT_MODE 1


// - - - - - - - - : variables


static stock 
	#if (defined _streamer_included && defined _INC_open_mp)
		STREAMER_TAG_OBJECT: _ext_cfp_obj_cam [MAX_PLAYERS],
	#else
		_ext_cfp_obj_cam [MAX_PLAYERS],
	#endif

	bool: _ext_cfp_crouched_cam [MAX_PLAYERS],
	bool: _ext_cfp_aim_cam [MAX_PLAYERS],
	bool: _ext_cfp_in_swimming [MAX_PLAYERS],
	bool: _ext_cfp_use_in_vehicle [MAX_PLAYERS],
	Float: _ext_cfp_cam_f_positions [MAX_PLAYERS] [5],
	Float: _ext_cfp_cam_h_positions [MAX_PLAYERS] [5]
;

new stock 
	bool: _ext_cfp_in_first_cam [MAX_PLAYERS]
;


// - - - - - - - - : functions


stock ResetCamPosFirstPersonPlayer (
	playerid
) {
	// FRONT
	_ext_cfp_cam_f_positions [playerid] [0] = 0.28; // FOOT - [ 0.28 ]
	_ext_cfp_cam_f_positions [playerid] [1] = 0.7; // SWIM - [ 0.7 ]
	_ext_cfp_cam_f_positions [playerid] [2] = 0.4; // CROUCH - [ 0.4 ]
	_ext_cfp_cam_f_positions [playerid] [3] = 0.2; // VEH - [ 0.2 ]
	_ext_cfp_cam_f_positions [playerid] [4] = 0.5; // AIM - [ 0.5 ]

	// HEIGHT
	_ext_cfp_cam_h_positions [playerid] [0] = 0.7; // FOOT - [ 0.7 ]
	_ext_cfp_cam_h_positions [playerid] [1] = 0.55; // SWIM - [ 0.55 ]
	_ext_cfp_cam_h_positions [playerid] [2] = 0.07; // CROUCH - [ 0.07 ]
	_ext_cfp_cam_h_positions [playerid] [3] = 0.7; // VEH - [ 0.7 ]
	_ext_cfp_cam_h_positions [playerid] [4] = 0.52; // AIM - [ 0.52 ]
	return
		1
	;
}

stock SetCamPositionFirstPersonPlayer (
	playerid,
	Float: position, 
	type = EXT_FC_FOOT_TYPE,
	mode = EXT_FC_FRONT_MODE
) {
	if (!EXT_FC_FRONT_MODE)
		_ext_cfp_cam_f_positions [playerid] [type] = position;
	else
        _ext_cfp_cam_h_positions [playerid] [type] = position;
	return 
		1
	;
}

stock SetCamFirstPersonPlayer (
	playerid,
	bool: use_in_veh = true
) {
	_ext_cfp_in_first_cam [playerid] = true;
	_ext_cfp_use_in_vehicle [playerid] = use_in_veh;
	#if (defined _streamer_included && defined _INC_open_mp)
		DestroyDynamicObject (_ext_cfp_obj_cam [playerid]);
		_ext_cfp_obj_cam [playerid] = CreateDynamicObject (INC_FC_OBJECT_CAM, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		AttachDynamicObjectToPlayer (_ext_cfp_obj_cam [playerid], playerid, 0.0, _ext_cfp_cam_f_positions [playerid] [EXT_FC_FOOT_TYPE], _ext_cfp_cam_h_positions [playerid] [EXT_FC_FOOT_TYPE], 0.0, 0.0, 0.0);
		AttachCameraToDynamicObject (playerid, _ext_cfp_obj_cam [playerid]);
	#else
		DestroyObject (_ext_cfp_obj_cam [playerid]);
		_ext_cfp_obj_cam [playerid] = CreateObject (INC_FC_OBJECT_CAM, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
		AttachObjectToPlayer (_ext_cfp_obj_cam [playerid], playerid, 0.0, _ext_cfp_cam_f_positions [playerid] [EXT_FC_FOOT_TYPE], _ext_cfp_cam_h_positions [playerid] [EXT_FC_FOOT_TYPE], 0.0, 0.0, 0.0);
		AttachCameraToObject (playerid, _ext_cfp_obj_cam [playerid]);
	#endif
	return 
		1
	;
}

stock CancelCamFirstPersonPlayer (
	playerid,
	bool: cam_behind = true
) {
	if (cam_behind)
		SetCameraBehindPlayer (playerid);
	_ext_cfp_in_first_cam [playerid] = false;
	#if (defined _streamer_included && defined _INC_open_mp)
		DestroyDynamicObject (_ext_cfp_obj_cam [playerid]);
	#else
		DestroyObject (_ext_cfp_obj_cam [playerid]);
	#endif
	return 
		1
	;
}

#define IsCamFirstPersonPlayer(%0) _ext_cfp_in_first_cam [%0]


// - - - - - - - - : hookbacks


public OnPlayerConnect (
	playerid
) {
	ResetCamPosFirstPersonPlayer (playerid);

	_ext_cfp_in_first_cam [playerid] = false;
	_ext_cfp_use_in_vehicle [playerid] = false;
	_ext_cfp_crouched_cam [playerid] = false;
	_ext_cfp_aim_cam [playerid] = false;
	_ext_cfp_in_swimming [playerid] = false;
    #if (defined __OnPlayerConnect_ext_cfp)
        return 
            __OnPlayerConnect_ext_cfp (
				playerid
            )
        ;
    #else 
        return 
            1
        ;
    #endif
}

public OnPlayerSpawn (
	playerid
) {
	if (IsCamFirstPersonPlayer (playerid)) {

		new 
			_ext_cfp_anim = GetPlayerAnimationIndex (playerid)
		;
		if (!(((_ext_cfp_anim >= 1160) && (_ext_cfp_anim <= 1163)) || (_ext_cfp_anim == 1167) || (_ext_cfp_anim == 1365) || (_ext_cfp_anim == 1643) || (_ext_cfp_anim == 1453) || (_ext_cfp_anim == 220))) {
			SetCamFirstPersonPlayer (playerid, _ext_cfp_use_in_vehicle [playerid]);
		}

		//////////////////

		if (GetPlayerSpecialAction (playerid) != SPECIAL_ACTION_DUCK && !IsPlayerInAnyVehicle (playerid)) {
			#if (defined _streamer_included && defined _INC_open_mp)
				AttachCameraToDynamicObject (playerid, _ext_cfp_obj_cam [playerid]);
			#else
				AttachCameraToObject (playerid, _ext_cfp_obj_cam [playerid]);
			#endif
		}

		//////////////////

		static
			_ext_cfp_animlib [2] [32] = {0, ...}
		;
		GetAnimationName (GetPlayerAnimationIndex (playerid), _ext_cfp_animlib [0], 32, _ext_cfp_animlib [1], 32);
		if (!(!strcmp (_ext_cfp_animlib [0], "SWIM") && !IsPlayerInAnyVehicle (playerid)) && _ext_cfp_in_swimming  [playerid]) {
			SetCamFirstPersonPlayer (playerid, _ext_cfp_use_in_vehicle [playerid]);
			_ext_cfp_in_swimming [playerid] = false;
		}
	}
    #if (defined __OnPlayerSpawn_ext_cfp)
        return 
            __OnPlayerSpawn_ext_cfp (
				playerid
            )
        ;
    #else 
        return 
            1
        ;
    #endif
}

public OnPlayerEnterVehicle (
	playerid, 
	vehicleid, 
	ispassenger
) {
	if (IsCamFirstPersonPlayer (playerid) && _ext_cfp_use_in_vehicle [playerid]) {
		#if (defined _streamer_included && defined _INC_open_mp)
			DestroyDynamicObject (_ext_cfp_obj_cam [playerid]);
			_ext_cfp_obj_cam [playerid] = CreateDynamicObject (INC_FC_OBJECT_CAM, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			AttachDynamicObjectToPlayer (_ext_cfp_obj_cam [playerid], playerid, 0.0, _ext_cfp_cam_f_positions [playerid] [EXT_FC_VEH_TYPE], _ext_cfp_cam_h_positions [playerid] [EXT_FC_VEH_TYPE], 0.0, 0.0, 0.0);
			AttachCameraToDynamicObject (playerid, _ext_cfp_obj_cam [playerid]);
		#else
			DestroyObject (_ext_cfp_obj_cam [playerid]);
			_ext_cfp_obj_cam [playerid] = CreateObject (INC_FC_OBJECT_CAM, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			AttachObjectToPlayer (_ext_cfp_obj_cam [playerid], playerid, 0.0, _ext_cfp_cam_f_positions [playerid] [EXT_FC_VEH_TYPE], _ext_cfp_cam_h_positions [playerid] [EXT_FC_VEH_TYPE], 0.0, 0.0, 0.0);
			AttachCameraToObject (playerid, _ext_cfp_obj_cam [playerid]);
		#endif
	} else if (IsCamFirstPersonPlayer (playerid)) {
		#if (defined _streamer_included && defined _INC_open_mp)
			DestroyDynamicObject (_ext_cfp_obj_cam [playerid]);
		#else
			DestroyObject (_ext_cfp_obj_cam [playerid]);
		#endif
		SetCameraBehindPlayer (playerid);
	}
	#if (defined __OnPlayerEnterVehicle_ext_cfp)
        return 
            __OnPlayerEnterVehicle_ext_cfp (
				playerid, 
				vehicleid,
				ispassenger
			)
        ;
    #else 
        return 
            1
        ;
    #endif
}

public OnPlayerExitVehicle (
	playerid, 
	vehicleid
) {
	if (IsCamFirstPersonPlayer (playerid)) {
		SetCamFirstPersonPlayer(playerid, _ext_cfp_use_in_vehicle [playerid]);
	}
	#if (defined __OnPlayerExitVehicle_ext_cfp)
        return 
            __OnPlayerExitVehicle_ext_cfp (
				playerid, 
				vehicleid
			)
        ;
    #else 
        return 
            1
        ;
    #endif
}


public OnPlayerKeyStateChange (
	playerid, 
	newkeys, 
	oldkeys
) {
	if (IsCamFirstPersonPlayer (playerid)) {
		static
			_ext_cfp_animlib [2] [32] = {0, ...}
		;
		GetAnimationName (GetPlayerAnimationIndex (playerid), _ext_cfp_animlib [0], 32, _ext_cfp_animlib [1], 32);
		if ((newkeys & (KEY_HANDBRAKE | KEY_FIRE)) && strcmp (_ext_cfp_animlib [0], "SWIM") && !IsPlayerInAnyVehicle (playerid)) {
			_ext_cfp_aim_cam [playerid] = true;
			#if (defined _streamer_included && defined _INC_open_mp)
				AttachDynamicObjectToPlayer (_ext_cfp_obj_cam [playerid], playerid, 0.0, _ext_cfp_cam_f_positions [playerid] [EXT_FC_AIM_TYPE], _ext_cfp_cam_h_positions [playerid] [EXT_FC_AIM_TYPE], 0.0, 0.0, 0.0);
				AttachCameraToDynamicObject (playerid, _ext_cfp_obj_cam [playerid]);
			#else
				AttachObjectToPlayer (_ext_cfp_obj_cam [playerid], playerid, 0.0, _ext_cfp_cam_f_positions [playerid] [EXT_FC_AIM_TYPE], _ext_cfp_cam_h_positions [playerid] [EXT_FC_AIM_TYPE], 0.0, 0.0, 0.0);
				AttachCameraToObject (playerid, _ext_cfp_obj_cam [playerid]); 
			#endif
		} else if ((newkeys & (KEY_SPRINT)) && (!strcmp (_ext_cfp_animlib [0], "SWIM") && !IsPlayerInAnyVehicle (playerid))) {
			_ext_cfp_in_swimming [playerid] = true;
			#if (defined _streamer_included && defined _INC_open_mp)
				AttachDynamicObjectToPlayer (_ext_cfp_obj_cam [playerid], playerid, 0.0, _ext_cfp_cam_f_positions [playerid] [EXT_FC_SWIM_TYPE], _ext_cfp_cam_h_positions [playerid] [EXT_FC_SWIM_TYPE], 0.0, 0.0, 0.0);
				AttachCameraToDynamicObject (playerid, _ext_cfp_obj_cam [playerid]);
			#else
				AttachObjectToPlayer (_ext_cfp_obj_cam [playerid], playerid, 0.0, _ext_cfp_cam_f_positions [playerid] [EXT_FC_SWIM_TYPE], _ext_cfp_cam_h_positions [playerid] [EXT_FC_SWIM_TYPE], 0.0, 0.0, 0.0);
				AttachCameraToObject (playerid, _ext_cfp_obj_cam [playerid]); 
			#endif
		} else if ((newkeys & (KEY_UP)) && (!strcmp (_ext_cfp_animlib [0], "SWIM") && !IsPlayerInAnyVehicle (playerid))) {
			_ext_cfp_in_swimming [playerid] = true;
			#if (defined _streamer_included && defined _INC_open_mp)
				AttachDynamicObjectToPlayer (_ext_cfp_obj_cam [playerid], playerid, 0.0, _ext_cfp_cam_f_positions [playerid] [EXT_FC_SWIM_TYPE], _ext_cfp_cam_h_positions [playerid] [EXT_FC_SWIM_TYPE], 0.0, 0.0, 0.0);
				AttachCameraToDynamicObject (playerid, _ext_cfp_obj_cam [playerid]);
			#else
				AttachObjectToPlayer (_ext_cfp_obj_cam [playerid], playerid, 0.0, _ext_cfp_cam_f_positions [playerid] [EXT_FC_SWIM_TYPE], _ext_cfp_cam_h_positions [playerid] [EXT_FC_SWIM_TYPE], 0.0, 0.0, 0.0);
				AttachCameraToObject (playerid, _ext_cfp_obj_cam [playerid]); 
			#endif
		} else if((((newkeys & (KEY_SPRINT)) != (KEY_SPRINT)) && ((oldkeys & (KEY_SPRINT)) == (KEY_SPRINT))) && (!strcmp (_ext_cfp_animlib [0], "SWIM") && !IsPlayerInAnyVehicle (playerid))) {
			_ext_cfp_in_swimming [playerid] = false;
			SetCamFirstPersonPlayer (playerid, _ext_cfp_use_in_vehicle [playerid]);
		} else if((((newkeys & (KEY_UP)) != (KEY_UP)) && ((oldkeys & (KEY_UP)) == (KEY_UP))) && (!strcmp (_ext_cfp_animlib [0], "SWIM") && !IsPlayerInAnyVehicle (playerid))) {
			_ext_cfp_in_swimming [playerid] = false;
			SetCamFirstPersonPlayer (playerid, _ext_cfp_use_in_vehicle [playerid]);
		}
	}
	#if (defined __OnPlayerKeyStateChange_ext_cfp)
        return 
            __OnPlayerKeyStateChange_ext_cfp (
				playerid, 
				newkeys, 
				oldkeys
			)
        ;
    #else 
        return 
            1
        ;
    #endif
}

public OnPlayerUpdate (
	playerid
) {
	if (IsCamFirstPersonPlayer (playerid)) {
		new 
			_ext_cfp_anim = GetPlayerAnimationIndex (playerid)
		;
		if ((((_ext_cfp_anim >= 1160) && (_ext_cfp_anim <= 1163)) || (_ext_cfp_anim == 1167) || (_ext_cfp_anim == 1365) || (_ext_cfp_anim == 1643) || (_ext_cfp_anim == 1453) || (_ext_cfp_anim == 220)) && GetPlayerSpecialAction (playerid) != SPECIAL_ACTION_DUCK) {
			#if (defined _streamer_included && defined _INC_open_mp)
				AttachDynamicObjectToPlayer (_ext_cfp_obj_cam [playerid], playerid, 0.0, _ext_cfp_cam_f_positions [playerid] [EXT_FC_AIM_TYPE], _ext_cfp_cam_h_positions [playerid] [EXT_FC_AIM_TYPE], 0.0, 0.0, 0.0);
				AttachCameraToDynamicObject (playerid, _ext_cfp_obj_cam [playerid]);
			#else
				AttachObjectToPlayer (_ext_cfp_obj_cam [playerid], playerid, 0.0, _ext_cfp_cam_f_positions [playerid] [EXT_FC_AIM_TYPE], _ext_cfp_cam_h_positions [playerid] [EXT_FC_AIM_TYPE], 0.0, 0.0, 0.0);
				AttachCameraToObject (playerid, _ext_cfp_obj_cam [playerid]);
			#endif
		} else if (GetPlayerCameraMode (playerid) != 46 && _ext_cfp_aim_cam [playerid]) {
			_ext_cfp_aim_cam [playerid] = false;
			if (!_ext_cfp_crouched_cam [playerid]) {
				SetCamFirstPersonPlayer (playerid, _ext_cfp_use_in_vehicle [playerid]);
			} else {
				#if (defined _streamer_included && defined _INC_open_mp)
					DestroyDynamicObject (_ext_cfp_obj_cam [playerid]);
					_ext_cfp_obj_cam [playerid] = CreateDynamicObject (INC_FC_OBJECT_CAM, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
					AttachDynamicObjectToPlayer (_ext_cfp_obj_cam [playerid], playerid, 0.0, _ext_cfp_cam_f_positions [playerid] [EXT_FC_CROUCH_TYPE], _ext_cfp_cam_h_positions [playerid] [EXT_FC_CROUCH_TYPE], 0.0, 0.0, 0.0);
					AttachCameraToDynamicObject (playerid, _ext_cfp_obj_cam [playerid]);
				#else
					DestroyObject (_ext_cfp_obj_cam [playerid]);
					_ext_cfp_obj_cam [playerid] = CreateObject (INC_FC_OBJECT_CAM, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
					AttachObjectToPlayer (_ext_cfp_obj_cam [playerid], playerid, 0.0, _ext_cfp_cam_f_positions [playerid] [EXT_FC_CROUCH_TYPE], _ext_cfp_cam_h_positions [playerid] [EXT_FC_CROUCH_TYPE], 0.0, 0.0, 0.0);
					AttachCameraToObject (playerid, _ext_cfp_obj_cam [playerid]);
				#endif
			}
		} else if (GetPlayerSpecialAction (playerid) != SPECIAL_ACTION_DUCK && _ext_cfp_crouched_cam [playerid]) {
			_ext_cfp_crouched_cam [playerid] = false;
			SetCamFirstPersonPlayer (playerid, _ext_cfp_use_in_vehicle [playerid]);
			//AttachCameraToObject (playerid, _ext_cfp_obj_cam [playerid]);
		} else if (GetPlayerSpecialAction (playerid) == SPECIAL_ACTION_DUCK && !_ext_cfp_crouched_cam [playerid]) {
			#if (defined _streamer_included && defined _INC_open_mp)
				DestroyDynamicObject (_ext_cfp_obj_cam [playerid]);
				_ext_cfp_obj_cam [playerid] = CreateDynamicObject (INC_FC_OBJECT_CAM, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
				AttachDynamicObjectToPlayer (_ext_cfp_obj_cam [playerid], playerid, 0.0, _ext_cfp_cam_f_positions [playerid] [EXT_FC_CROUCH_TYPE], _ext_cfp_cam_h_positions [playerid] [EXT_FC_CROUCH_TYPE], 0.0, 0.0, 0.0);
				AttachCameraToDynamicObject (playerid, _ext_cfp_obj_cam [playerid]);
			#else
				DestroyObject (_ext_cfp_obj_cam [playerid]);
				_ext_cfp_obj_cam [playerid] = CreateObject (INC_FC_OBJECT_CAM, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
				AttachObjectToPlayer (_ext_cfp_obj_cam [playerid], playerid, 0.0, _ext_cfp_cam_f_positions [playerid] [EXT_FC_CROUCH_TYPE], _ext_cfp_cam_h_positions [playerid] [EXT_FC_CROUCH_TYPE], 0.0, 0.0, 0.0);
				AttachCameraToObject (playerid, _ext_cfp_obj_cam [playerid]);
			#endif
			_ext_cfp_crouched_cam [playerid] = true;
		} 
	}
    #if (defined __OnPlayerUpdate_ext_cfp)
        return 
            __OnPlayerUpdate_ext_cfp (
				playerid
            )
        ;
    #else 
        return 
            1
        ;
    #endif
}


// - - - - - - - - : hooks 


#if (defined _ALS_OnPlayerConnect)
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect __OnPlayerConnect_ext_cfp
#if (defined __OnPlayerConnect_ext_cfp)
	forward __OnPlayerConnect_ext_cfp (
        playerid
    );
#endif


#if (defined _ALS_OnPlayerSpawn)
    #undef OnPlayerSpawn
#else
    #define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn __OnPlayerSpawn_ext_cfp
#if (defined __OnPlayerSpawn_ext_cfp)
	forward  __OnPlayerSpawn_ext_cfp (
		playerid
	);
#endif


#if (defined _ALS_OnPlayerEnterVehicle)
    #undef OnPlayerEnterVehicle
#else
    #define _ALS_OnPlayerEnterVehicle
#endif
#define OnPlayerEnterVehicle __OnPlayerEnterVehicle_ext_cfp
#if (defined __OnPlayerEnterVehicle_ext_cfp)
	forward __OnPlayerEnterVehicle_ext_cfp (
		playerid, 
		vehicleid,
		ispassenger
	);
#endif


#if (defined _ALS_OnPlayerExitVehicle)
    #undef OnPlayerExitVehicle
#else
    #define _ALS_OnPlayerExitVehicle
#endif
#define OnPlayerExitVehicle __OnPlayerExitVehicle_ext_cfp
#if (defined __OnPlayerExitVehicle_ext_cfp)
	forward __OnPlayerExitVehicle_ext_cfp (
		playerid, 
		vehicleid
	);
#endif


#if (defined _ALS_OnPlayerKeyStateChange)
    #undef OnPlayerKeyStateChange
#else
    #define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange __OnPlayerKeyStateChange_ext_cfp
#if (defined __OnPlayerKeyStateChange_ext_cfp)
	forward __OnPlayerKeyStateChange_ext_cfp (
		playerid, 
		newkeys, 
		oldkeys
	);
#endif


#if (defined _ALS_OnPlayerUpdate)
    #undef OnPlayerUpdate
#else
    #define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate __OnPlayerUpdate_ext_cfp
#if (defined __OnPlayerUpdate_ext_cfp)
	forward __OnPlayerUpdate_ext_cfp (
        playerid
    );
#endif

// - - - - - - - - : end.cfp.ext


/*

ooo        ooooo               .   oooo                  oooooooooooo                 .               
`88.       .888'             .o8   `888                  `888'     `8               .o8               
 888b     d'888   .oooo.   .o888oo  888 .oo.              888         oooo    ooo .o888oo             
 8 Y88. .P  888  `P  )88b    888    888P"Y88b             888oooo8     `88b..8P'    888               
 8  `888'   888   .oP"888    888    888   888             888    "       Y888'      888               
 8    Y     888  d8(  888    888 .  888   888             888       o  .o8"'88b     888 . .o. .o. .o. 
o8o        o888o `Y888""8o   "888" o888o o888o           o888ooooood8 o88'   888o   "888" Y8P Y8P Y8P 
                                                                                                      
*/


// - - - - - - - - : natives


/*

native MathRandomEx (val_min, val_max = 0);
native MathPow (base, exponent = 2);
native MathSqRoot (number. exponent = 2);
native MathSqRootRest (number. exponent = 2);


*/


// - - - - - - - - : functions


stock MathRandomEx (
    val_min,
    val_max = 0
) {
	new
		__ext_math_val_min = val_min,
		__ext_math_val_max = val_max
	;
    if (__ext_math_val_max == __ext_math_val_min)
        return __ext_math_val_min;
    else
        if (__ext_math_val_min >= 0 && __ext_math_val_max >= 0)
            if (__ext_math_val_max >= __ext_math_val_min)
                return __ext_math_val_min + random ((__ext_math_val_max - __ext_math_val_min) + 1);
            else
                return __ext_math_val_max + random ((__ext_math_val_min - __ext_math_val_max) + 1);
        else if (__ext_math_val_min <= 0 && __ext_math_val_max <= 0)
            if (-__ext_math_val_max >= -__ext_math_val_min)
                return -(-__ext_math_val_min + random (-(__ext_math_val_max - __ext_math_val_min) + 1));
            else
                return -(-__ext_math_val_max + random (-(__ext_math_val_min - __ext_math_val_max) + 1));
        else
            if (__ext_math_val_max >= __ext_math_val_min)
                return (__ext_math_val_min + random ((__ext_math_val_max - __ext_math_val_min) + 1));
            else
                return (__ext_math_val_max + random ((__ext_math_val_min - __ext_math_val_max) + 1));
} 


stock MathPow (
	base, 
	exponent = 2
) {
	new 
		__ext_math_result = 1
	;
	for (new __ext_i = 0; __ext_i < exponent; __ext_i++) {
		__ext_math_result *= base;
	}
	return 
		__ext_math_result
	;
}
#define MathPower MathPow


stock MathSqRoot (
	number,
	exponent = 2
) {
    if (exponent <= 0 || number < 0) 
		return 
			0
		;
    new 
		__ext_math_result = 0
	;
    while (MathPow (__ext_math_result + 1, exponent) <= number) {
        __ext_math_result ++;
    }
    return 
		__ext_math_result
	;
}


stock MathSqRootRest (
	number,
	exponent = 2
) {
	return 
		MathSqRoot (number - MathPow (MathSqRoot (number, exponent), exponent), exponent)
	;
}