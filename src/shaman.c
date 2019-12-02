/*******************************************************************\
* A small, native C utility for fetching weather                    *
* Copyright (C) 2013-2014, Sam Stuewe                               *
*                                                                   *
* This program is free software; you can redistribute it and/or     *
* modify it under the terms of the GNU General Public License       *
* as published by the Free Software Foundation; either version 2    *
* of the License, or (at your option) any later version.            *
*                                                                   *
* This program is distributed in the hope that it will be useful,   *
* but WITHOUT ANY WARRANTY; without even the implied warranty of    *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the      *
* GNU General Public License for more details.                      *
*                                                                   *
* You should have received a copy of the GNU General Public License *
* along with this program; if not, write to the Free Software       *
* Foundation, Inc., 51 Franklin Street, Fifth Floor,                *
* Boston, MA  02110-1301, USA.                                      *
\*******************************************************************/

// Libraries //
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "weather.h"
#include "usage.h"

/**
 * If you fork this code, please DO NOT use this key.
 * Getting an API key with OWM is free, but this key is exclusively
 * for shaman
 */
#define OWMAPIKEY "83a3a133bc7541a6608536d490f7a11d"

// Main Function //
signed
main (signed argc, char * argv []) {

    char flag_scale   = 'i',  flag_refresh = 0,
         flag_verbose = 0,    flag_quiet   = 0;

    char * format     = NULL, * location   = NULL;

    if ( argc <= 1 ) {
        _usage(1);
    } else {
        static struct option os [] = {
            /* Flags */
            { "help",     no_argument,       0, 'h' },
            { "imperial", no_argument,       0, 'i' },
            { "metric",   no_argument,       0, 'm' },
            { "refresh",  no_argument,       0, 'r' },
            { "verbose",  no_argument,       0, 'v' },
            { "quiet",    no_argument,       0, 'q' },
            /* Swtiches */
            { "format",   required_argument, 0, 'f' },
            { "location", required_argument, 0, 'l' },
            { 0,          0,                 0, 0   },
        };

        for ( signed c = 0, oi = 0; c != -1;
              c = getopt_long(argc, argv, "himrvq:f:l:", os, &oi) ) {

            unsigned long optarg_len;

            switch ( c ) {
                case 'h':
                    _usage(0);

                case 'i':
                    flag_scale = 'i'; break;

                case 'm':
                    flag_scale = 'm'; break;

                case 'r':
                    flag_refresh ++; break;

                case 'v':
                    flag_verbose ++; break;

                case 'q':
                    flag_quiet ++; break;

                case 'f':
                    optarg_len = strlen(optarg) + 1;
                    format = malloc(optarg_len);
                    strncpy(format, optarg, optarg_len);
                    break;

                case 'l':
                    optarg_len = strlen(optarg) + 1;
                    location = malloc(optarg_len);
                    strncpy(location, optarg, optarg_len);
                    break;
            }
        }
    }

    if ( !format ) {
        format = malloc(11);
        snprintf(format, 11, "%%c (%%t°%c)", (flag_scale == 'm' ? 'C' : 'F'));
    }

    if ( !location ) { _usage(1); }

    struct weather * wthr = owm_easy('q', location, flag_scale, NULL,
                                     flag_refresh ? 0 : 600, OWMAPIKEY,
                                     flag_verbose);

    if ( location )   { free(location);   }

    char output_string [BUFFER_SIZE];
    strfweather(output_string, BUFFER_SIZE, format, wthr);

    if ( format ) { free(format); }

    if ( flag_quiet ) {
        exit((signed )wthr->weather_code / 100); // weather group as exit status
    } else {
        printf("%s\n", output_string);
    } return 0;
}

// vim: set ts=4 sw=4 et:
