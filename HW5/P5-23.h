/*	==================== search ====================	Searches for year and prints year, picture, and	director.	   Pre    list has been created	          user has selected search option	   Post   year printed or error message*/void search (LIST* list){//	Local Definitions 	short    year;	bool     found;		PICTURE  pSrchArgu;	PICTURE* pPic;	//	Statements 	printf("Enter a four digit year: ");	scanf ("%hd", &year);	pSrchArgu.year = year;		found = searchList (list, &pSrchArgu, 	                    (void**)&pPic);		if (found)	    printf("%hd %-40s %s\n",	            pPic->year, pPic->picture, pPic->director);	else	    printf("Sorry, but %d is not available.\n", year);	return;}	// search 