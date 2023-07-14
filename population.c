#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start;
    do
    {
        start = get_int("Start size: ");

    }while(start < 9);

    // TODO: Prompt for end size
    int end;

    do
    {
        end = get_int("End size: ");

    }while(end < start);

    // TODO: Calculate number of years until we reach threshold
    int growth = start / 3;
    int pass = start / 4;
    int sum = start;
    int counter = 0;
    while(sum < end)
    {

        sum += (growth - pass);
        pass = sum / 4;
        growth = sum / 3;
        counter++;
    }

    // TODO: Print number of years
    printf("Years: %i", counter);

}
