"25 /usr/local/lib/cpm/include80/stdio.h
[s S1 `*c 1 `i 1 `*c 1 `us 1 `c 1 ]
"85
[v _fclose `(i 0 e ]
"86
[v _fflush `(i 0 e ]
"87
[v _fgetc `(i 0 e ]
"88
[v _ungetc `(i 0 e ]
"89
[v _fputc `(i 0 e ]
"90
[v _getw `(i 0 e ]
"91
[v _putw `(i 0 e ]
"92
[v _gets `(*c 0 e ]
"93
[v _puts `(i 0 e ]
"94
[v _fputs `(i 0 e ]
"95
[v _fread `(i 0 e ]
"96
[v _fwrite `(i 0 e ]
"97
[v _fseek `(i 0 e ]
"98
[v _rewind `(i 0 e ]
"99
[v _setbuf `(i 0 e ]
"100
[v _printf `(i 0 e ]
"101
[v _fprintf `(i 0 e ]
"102
[v _sprintf `(i 0 e ]
"103
[v _scanf `(i 0 e ]
"104
[v _fscanf `(i 0 e ]
"105
[v _sscanf `(i 0 e ]
"106
[v _remove `(i 0 e ]
"107
[v _fopen `(*S1 0 e ]
"108
[v _freopen `(*S1 0 e ]
"109
[v _fdopen `(*S1 0 e ]
"110
[v _ftell `(l 0 e ]
"111
[v _fgets `(*c 0 e ]
"112
[v __bufallo `(*c 0 e ]
"7 /usr/local/lib/cpm/include80/stdlib.h
[v _ptrdiff_t `i 1 t ]
"8
[v _size_t `ui 1 t ]
"23
[v _atof `(d 0 e ]
"24
[v _atoi `(i 0 e ]
"25
[v _atol `(l 0 e ]
"26
[v _rand `(i 0 e ]
"27
[v _srand `(v 0 e ]
"28
[v _calloc `(*v 0 e ]
"29
[v _free `(v 0 e ]
"30
[v _malloc `(*v 0 e ]
"31
[v _realloc `(*v 0 e ]
"32
[v _abort `(v 0 e ]
"33
[v _exit `(v 0 e ]
"34
[v _getenv `(*c 0 e ]
"35
[v _system `(i 0 e ]
"36
[v ___qsort_compf `*(i 1 t ]
"37
[v _qsort `(v 0 e ]
"38
[v _abs `(i 0 e ]
"39
[v _labs `(l 0 e ]
"19 /usr/local/lib/cpm/include80/string.h
[v _memcpy `(*v 0 e ]
"20
[v _memmove `(*v 0 e ]
"21
[v _strcpy `(*c 0 e ]
"22
[v _strncpy `(*c 0 e ]
"23
[v _strcat `(*c 0 e ]
"24
[v _strncat `(*c 0 e ]
"25
[v _memcmp `(i 0 e ]
"26
[v _strcmp `(i 0 e ]
"27
[v _strcasecmp `(i 0 e ]
"29
[v _strncmp `(i 0 e ]
"30
[v _strncasecmp `(i 0 e ]
"33
[v _memchr `(*v 0 e ]
"37
[v _strstr `(*c 0 e ]
"38
[v _strtok `(*c 0 e ]
"39
[v _memset `(*v 0 e ]
"40
[v _strerror `(*c 0 e ]
"41
[v _strlen `(ui 0 e ]
"42
[v _strchr `(*c 0 e ]
"44
[v _index `(*c 0 e ]
"45
[v _strrchr `(*c 0 e ]
"47
[v _rindex `(*c 0 e ]
"48
[v _strcasestr `(*c 0 e ]
"50
[v _strncasestr `(*c 0 e ]
"19 main-ansi-old.c
[v _demonstrate_variables_and_types `(v 0 e ]
"20
[v _demonstrate_operators `(v 0 e ]
"21
[v _demonstrate_control_flow `(v 0 e ]
"22
[v _demonstrate_functions_and_point `(v 0 e ]
"23
[v _demonstrate_arrays_and_strings `(v 0 e ]
"24
[v _demonstrate_structs_unions_enum `(v 0 e ]
"25
[v _demonstrate_file_io `(v 0 e ]
"28
[v _main `(i 1 e ]
{
[e :U _main ]
[e ( _printf :s 1 ]
[e ( _printf :s 2 ]
[e ( _printf :s 3 ]
"33
[e ( _demonstrate_variables_and_types ..  ]
"34
[e ( _demonstrate_operators ..  ]
"35
[e ( _demonstrate_control_flow ..  ]
"36
[e ( _demonstrate_functions_and_point ..  ]
"37
[e ( _demonstrate_arrays_and_strings ..  ]
"38
[e ( _demonstrate_structs_unions_enum ..  ]
"39
[e ( _demonstrate_file_io ..  ]
[e ( _printf :s 4 ]
"42
[e ) -> 0 `i ]
[e $U 2 ]
"43
[e :U 2 ]
}
"46
[v _demonstrate_variables_and_types `(v 1 e ]
{
[e :U _demonstrate_variables_and_types ]
"47
[v _integer_var `i 1 a ]
[e = _integer_var -> 42 `i ]
"48
[v _float_var `f 1 a ]
[e = _float_var -> .3.14 `f ]
"49
[v _double_var `d 1 a ]
[e = _double_var .2.71828 ]
"50
[v _char_var `c 1 a ]
[e = _char_var -> 67 `c ]
"51
[v _bool_var `i 1 a ]
[e = _bool_var -> 1 `i ]
"53
[v _PI `f 1 a ]
[e = _PI -> .3.14159 `f ]
[e ( _printf :s 5 ]
[e ( _printf , , :s 6 _integer_var -> -> # _integer_var `i `ul ]
[e ( _printf , , :s 7 -> _float_var `d -> -> # _float_var `i `ul ]
[e ( _printf , , :s 8 _double_var -> -> # _double_var `i `ul ]
[e ( _printf , , :s 9 -> _char_var `i -> -> # _char_var `i `ul ]
[e ( _printf , , :s 10 _bool_var -> -> # _bool_var `i `ul ]
[e ( _printf , :s 11 -> _PI `d ]
"62
[e :U 3 ]
}
"65
[v _demonstrate_operators `(v 1 e ]
{
[e :U _demonstrate_operators ]
"66
[v _a `i 1 a ]
[e = _a -> 10 `i ]
[v _b `i 1 a ]
[e = _b -> 3 `i ]
"67
[v _x `i 1 a ]
[e = _x -> 10 `i ]
"68
[v _y `i 1 a ]
[e = _y -> 12 `i ]
"69
[v _cond `i 1 a ]
"70
[v _result_str `*c 1 a ]
[e ( _printf :s 12 ]
[e ( _printf , , :s 13 _a _b ]
[e ( _printf , :s 14 + _a _b ]
[e ( _printf , :s 15 % _a _b ]
[e ( _printf :s 16 ]
[e ( _printf , :s 17 & _x _y ]
[e ( _printf , :s 18 | _x _y ]
[e ( _printf , :s 19 << _x -> 1 `i ]
[e ( _printf :s 20 ]
"83
[e = _cond -> && > _a _b != _x -> 0 `i `i ]
[e ( _printf , :s 21 ? != _cond -> 0 `i : :s 22 :s 23 ]
[e = _result_str ? > _b -> 5 `i : :s 24 :s 25 ]
[e ( _printf , :s 26 _result_str ]
"87
[e :U 4 ]
}
"90
[v _demonstrate_control_flow `(v 1 e ]
{
[e :U _demonstrate_control_flow ]
"91
[v _i `i 1 a ]
[e = _i -> 5 `i ]
"92
[v _grade `c 1 a ]
[e = _grade -> 66 `c ]
"93
[v _j `i 1 a ]
"94
[v _k `i 1 a ]
[e = _k -> 0 `i ]
[e ( _printf :s 27 ]
"97
[e $ ! > _i -> 10 `i 6 ]
[e ( _printf :s 28 ]
"100
[e $U 7 ]
[e :U 6 ]
[e $ ! == _i -> 5 `i 8 ]
[e ( _printf :s 29 ]
"104
[e :U 8 ]
[e :U 7 ]
[e ( _printf , :s 30 -> _grade `i ]
"105
[e $U 10 ]
"106
[e :U 11 ]
[e ( _printf :s 31 ]
"108
[e $U 9 ]
"109
[e :U 12 ]
[e ( _printf :s 32 ]
"111
[e $U 9 ]
"112
[e :U 13 ]
[e ( _printf :s 33 ]
"114
[e $U 9 ]
"115
[e $U 9 ]
[e :U 10 ]
[\ _grade
	-> 65 `c 11
	-> 66 `c 12
	.. 13
]
[e :U 9 ]
[e ( _printf :s 34 ]
"118
[e = _j -> 0 `i ]
[e $U 17 ]
[e :U 14 ]
[e ( _printf , :s 35 _j ]
"120
[e :U 16 ]
[e ++ _j -> 1 `i ]
[e :U 17 ]
[e $ < _j -> 5 `i 14 ]
[e :U 15 ]
[e ( _printf :s 36 ]
[e ( _printf :s 37 ]
"124
[e $U 18 ]
[e :U 19 ]
[e ( _printf , :s 38 _k ]
"126
[e ++ _k -> 1 `i ]
"127
[e :U 18 ]
[e $ < _k -> 5 `i 19 ]
[e :U 20 ]
[e ( _printf :s 39 ]
"129
[e :U 5 ]
}
"133
[v _add_one_by_reference `(v 1 s ]
{
[v _num_ptr `*i 1 r ]
[e :U _add_one_by_reference ]
"134
[e ++ *U _num_ptr -> 1 `i ]
"135
[e :U 21 ]
}
"138
[v _factorial `(l 1 e ]
{
[v _n `i 1 r ]
[e :U _factorial ]
"139
[e $ ! <= _n -> 1 `i 23 ]
[e ) -> 1 `l ]
[e $U 22 ]
"140
[e :U 23 ]
[e ) * -> _n `l ( _factorial - _n -> 1 `i ]
[e $U 22 ]
"141
[e :U 22 ]
}
"143
[v _demonstrate_functions_and_point `(v 1 e ]
{
[e :U _demonstrate_functions_and_point ]
"144
[v _my_number `i 1 a ]
[e = _my_number -> 10 `i ]
"145
[v _fact_num `i 1 a ]
[e = _fact_num -> 6 `i ]
"146
[v _factorial_ptr `*(l 1 a ]
[e ( _printf :s 40 ]
"150
[e ( _add_one_by_reference &U _my_number ]
[e ( _printf , :s 41 _my_number ]
[e ( _printf , , :s 42 _fact_num ( _factorial _fact_num ]
"155
[e = _factorial_ptr &U _factorial ]
[e ( _printf , :s 43 ( *U _factorial_ptr -> 5 `i ]
"157
[e :U 24 ]
}
"160
[v _demonstrate_arrays_and_strings `(v 1 e ]
{
[e :U _demonstrate_arrays_and_strings ]
"161
[v _numbers `i -> 5 `x a ]
"162
[v _greeting `c -> 20 `x a ]
"163
[v _i `i 1 a ]
[e ( _printf :s 44 ]
"166
[e = _i -> 0 `i ]
[e $U 29 ]
[e :U 26 ]
"167
[e = *U + &U _numbers * -> _i `x -> -> # `i `i `x * + _i -> 1 `i -> 10 `i ]
"168
[e :U 28 ]
[e ++ _i -> 1 `i ]
[e :U 29 ]
[e $ < _i -> 5 `i 26 ]
[e :U 27 ]
[e ( _printf , :s 45 *U + &U _numbers * -> 2 `x -> -> # `i `i `x ]
[e ( _strcpy , &U _greeting :s 46 ]
[e ( _strcat , &U _greeting :s 47 ]
[e ( _printf , :s 48 &U _greeting ]
[e ( _printf , :s 49 -> ( _strlen &U _greeting `ul ]
"175
[e :U 25 ]
}
"181
[s S30 `c -> 50 `x `i 1 ]
[v _Employee `S30 1 t ]
[c F267
"184
-> 0 `i
"186
-> 1 `i
.. ]
[v _MachineState `F267 1 t ]
"188
[v _demonstrate_structs_unions_enum `(v 1 e ]
{
[e :U _demonstrate_structs_unions_enum ]
"189
[v _emp1 `S30 1 a ]
"190
[v _current_state `F267 1 a ]
[e = _current_state . `F267 1 ]
[e ( _printf :s 50 ]
[e ( _strcpy , &U . _emp1 0 :s 51 ]
"194
[e = . _emp1 1 -> 123 `i ]
[e ( _printf , , :s 52 &U . _emp1 0 . _emp1 1 ]
"197
[e $ ! == -> _current_state `i -> . `F267 1 `i 32 ]
[e ( _printf , :s 53 -> _current_state `i ]
"200
[e :U 32 ]
[e :U 31 ]
}
"203
[v _demonstrate_file_io `(v 1 e ]
{
[e :U _demonstrate_file_io ]
"204
[v _file_ptr `*S1 1 a ]
"205
[v _buffer `c -> 100 `x a ]
[e ( _printf :s 54 ]
[e = _file_ptr ( _fopen , :s 55 :s 56 ]
"211
[e $ ! == _file_ptr -> 0 `*v 34 ]
[e ( _printf :s 57 ]
"213
[e $U 33 ]
"215
[e :U 34 ]
[e ( _fprintf , _file_ptr :s 58 ]
"216
[e ( _fclose _file_ptr ]
[e ( _printf :s 59 ]
[e = _file_ptr ( _fopen , :s 60 :s 61 ]
"221
[e $ ! == _file_ptr -> 0 `*v 35 ]
[e ( _printf :s 62 ]
"223
[e $U 33 ]
"225
[e :U 35 ]
[e ( _printf :s 63 ]
"226
[e $U 36 ]
[e :U 37 ]
[e ( _printf , :s 64 &U _buffer ]
"228
[e :U 36 ]
[e $ != ( _fgets , , &U _buffer -> # _buffer `i _file_ptr -> 0 `*v 37 ]
[e :U 38 ]
"229
[e ( _fclose _file_ptr ]
"230
[e :U 33 ]
}
"29
[a 1 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 10 0 ]
"30
[a 2 61 61 32 83 104 111 119 99 97 115 101 32 80 111 114 116 97 116 105 108 32 100 97 32 76 105 110 103 117 97 103 101 109 32 67 32 40 65 78 83 73 41 10 0 ]
"31
[a 3 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 61 10 0 ]
"41
[a 4 10 68 101 109 111 110 115 116 114 97 99 97 111 32 99 111 110 99 108 117 105 100 97 32 99 111 109 32 115 117 99 101 115 115 111 46 10 0 ]
"55
[a 5 10 45 45 45 32 49 46 32 86 97 114 105 97 118 101 105 115 32 101 32 84 105 112 111 115 32 100 101 32 68 97 100 111 115 32 45 45 45 10 0 ]
"56
[a 6 73 110 116 101 103 101 114 58 32 37 100 32 40 116 97 109 97 110 104 111 58 32 37 108 117 32 98 121 116 101 115 41 10 0 ]
"57
[a 7 70 108 111 97 116 58 32 32 32 37 102 32 40 116 97 109 97 110 104 111 58 32 37 108 117 32 98 121 116 101 115 41 10 0 ]
"58
[a 8 68 111 117 98 108 101 58 32 32 37 102 32 40 116 97 109 97 110 104 111 58 32 37 108 117 32 98 121 116 101 115 41 10 0 ]
"59
[a 9 67 104 97 114 58 32 32 32 32 37 99 32 40 116 97 109 97 110 104 111 58 32 37 108 117 32 98 121 116 101 41 10 0 ]
"60
[a 10 66 111 111 108 58 32 32 32 32 37 100 32 40 116 97 109 97 110 104 111 58 32 37 108 117 32 98 121 116 101 41 10 0 ]
"61
[a 11 67 111 110 115 116 97 110 116 101 32 80 73 58 32 37 102 10 0 ]
"72
[a 12 10 45 45 45 32 50 46 32 79 112 101 114 97 100 111 114 101 115 32 45 45 45 10 0 ]
"73
[a 13 65 114 105 116 109 101 116 105 99 111 115 58 32 97 61 37 100 44 32 98 61 37 100 10 0 ]
"74
[a 14 32 32 83 111 109 97 32 40 97 32 43 32 98 41 32 32 32 32 32 32 61 32 37 100 10 0 ]
"75
[a 15 32 32 82 101 115 116 111 32 40 97 32 37 37 32 98 41 32 32 32 32 32 32 61 32 37 100 10 0 ]
"77
[a 16 10 66 105 116 45 97 45 98 105 116 58 32 120 61 49 48 32 40 48 120 65 41 44 32 121 61 49 50 32 40 48 120 67 41 10 0 ]
"78
[a 17 32 32 65 78 68 32 40 120 32 38 32 121 41 32 32 32 32 32 32 32 61 32 37 100 10 0 ]
"79
[a 18 32 32 79 82 32 32 40 120 32 124 32 121 41 32 32 32 32 32 32 32 61 32 37 100 10 0 ]
"80
[a 19 32 32 83 104 105 102 116 32 69 115 113 32 40 120 32 60 60 32 49 41 61 32 37 100 10 0 ]
"82
[a 20 10 76 111 103 105 99 111 115 32 101 32 84 101 114 110 97 114 105 111 58 10 0 ]
"84
[a 21 32 32 40 97 32 62 32 98 41 32 38 38 32 40 120 32 33 61 32 48 41 32 101 32 37 115 10 0 ]
[a 22 84 82 85 69 0 ]
[a 23 70 65 76 83 69 0 ]
"85
[a 24 98 32 101 32 109 97 105 111 114 32 113 117 101 32 53 0 ]
[a 25 98 32 110 97 111 32 101 32 109 97 105 111 114 32 113 117 101 32 53 0 ]
"86
[a 26 32 32 82 101 115 117 108 116 97 100 111 32 100 111 32 116 101 114 110 97 114 105 111 58 32 37 115 10 0 ]
"96
[a 27 10 45 45 45 32 51 46 32 67 111 110 116 114 111 108 101 32 100 101 32 70 108 117 120 111 32 45 45 45 10 0 ]
"98
[a 28 105 102 58 32 105 32 101 32 109 97 105 111 114 32 113 117 101 32 49 48 10 0 ]
"101
[a 29 105 102 58 32 105 32 101 32 101 120 97 116 97 109 101 110 116 101 32 53 10 0 ]
[a 30 115 119 105 116 99 104 58 32 65 32 110 111 116 97 32 101 32 37 99 46 32 0 ]
"107
[a 31 69 120 99 101 108 101 110 116 101 33 10 0 ]
"110
[a 32 77 117 105 116 111 32 66 111 109 33 10 0 ]
"113
[a 33 80 114 101 99 105 115 97 32 101 115 116 117 100 97 114 32 109 97 105 115 46 10 0 ]
"117
[a 34 102 111 114 32 108 111 111 112 58 32 0 ]
"119
[a 35 37 100 32 0 ]
"121
[a 36 10 0 ]
"123
[a 37 119 104 105 108 101 32 108 111 111 112 58 32 0 ]
"125
[a 38 37 100 32 0 ]
"128
[a 39 10 0 ]
"148
[a 40 10 45 45 45 32 52 46 32 70 117 110 99 111 101 115 32 101 32 80 111 110 116 101 105 114 111 115 32 45 45 45 10 0 ]
"151
[a 41 78 117 109 101 114 111 32 97 112 111 115 32 99 104 97 109 97 100 97 32 112 111 114 32 114 101 102 101 114 101 110 99 105 97 58 32 37 100 10 0 ]
"153
[a 42 70 97 116 111 114 105 97 108 32 100 101 32 37 100 32 101 32 37 108 100 10 0 ]
"156
[a 43 70 97 116 111 114 105 97 108 32 100 101 32 53 32 40 118 105 97 32 112 111 110 116 101 105 114 111 41 32 101 32 37 108 100 10 0 ]
"165
[a 44 10 45 45 45 32 53 46 32 65 114 114 97 121 115 32 101 32 83 116 114 105 110 103 115 32 45 45 45 10 0 ]
"169
[a 45 79 32 116 101 114 99 101 105 114 111 32 101 108 101 109 101 110 116 111 32 100 111 32 97 114 114 97 121 32 101 58 32 37 100 10 0 ]
"171
[a 46 79 108 97 0 ]
"172
[a 47 44 32 77 117 110 100 111 33 0 ]
"173
[a 48 83 116 114 105 110 103 32 102 105 110 97 108 58 32 37 115 10 0 ]
"174
[a 49 67 111 109 112 114 105 109 101 110 116 111 32 40 115 116 114 108 101 110 41 58 32 37 108 117 10 0 ]
"192
[a 50 10 45 45 45 32 54 46 32 83 116 114 117 99 116 115 44 32 85 110 105 111 110 115 32 101 32 69 110 117 109 115 32 45 45 45 10 0 ]
"193
[a 51 76 101 97 110 100 114 111 0 ]
"195
[a 52 69 109 112 114 101 103 97 100 111 58 32 37 115 32 40 73 68 58 32 37 100 41 10 0 ]
"198
[a 53 69 110 117 109 58 32 65 32 109 97 113 117 105 110 97 32 101 115 116 97 32 110 111 32 101 115 116 97 100 111 32 82 85 78 78 73 78 71 32 40 37 100 41 46 10 0 ]
"207
[a 54 10 45 45 45 32 55 46 32 69 110 116 114 97 100 97 32 101 32 83 97 105 100 97 32 100 101 32 65 114 113 117 105 118 111 115 32 40 70 105 108 101 32 73 47 79 41 32 45 45 45 10 0 ]
"210
[a 55 116 101 115 116 101 46 116 120 116 0 ]
[a 56 119 0 ]
"212
[a 57 69 114 114 111 32 97 111 32 97 98 114 105 114 32 111 32 97 114 113 117 105 118 111 32 112 97 114 97 32 101 115 99 114 105 116 97 33 10 0 ]
[a 58 79 108 97 32 100 111 32 109 117 110 100 111 32 100 111 32 67 33 10 0 ]
"217
[a 59 65 114 113 117 105 118 111 32 39 116 101 115 116 101 46 116 120 116 39 32 101 115 99 114 105 116 111 32 99 111 109 32 115 117 99 101 115 115 111 46 10 0 ]
"220
[a 60 116 101 115 116 101 46 116 120 116 0 ]
[a 61 114 0 ]
"222
[a 62 69 114 114 111 32 97 111 32 97 98 114 105 114 32 111 32 97 114 113 117 105 118 111 32 112 97 114 97 32 108 101 105 116 117 114 97 33 10 0 ]
[a 63 76 101 110 100 111 32 100 111 32 97 114 113 117 105 118 111 32 39 116 101 115 116 101 46 116 120 116 39 58 10 0 ]
"227
[a 64 32 32 62 32 37 115 0 ]
