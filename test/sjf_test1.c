int
main()
{
    int i;
    int j;
    for(i = 0; i < 9; i++){
        for(j = 0; j < 5; j++){
            PrintInt(100+i*10+j);
        }
        Sleep(1);
    }
}
