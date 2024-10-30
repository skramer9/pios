// returns 0 if the strings don't match and 1 if they do
int compareFilenames(char* x, char* y) {
    while(*x != ' ' && *y != ' ') {
        if (*x != *y) { //if the characters aren't the same, end
	    return 0;
	}
	if (*x == *y) { //if they are, move on to the next chars
	    x++;
	    y++;
        }
    }
    return 1; //if the program makes it here, the strings matched
}
