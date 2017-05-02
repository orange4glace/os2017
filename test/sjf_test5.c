int
main()
{
    int i, j;
    j = 0;
    for(i = 0; i < 9; i++){
    	for (j = 0; j < 1000; j ++) {
    		j++;
    	}
        PrintInt(i*10 + 100);
        Sleep(1);
    }
}