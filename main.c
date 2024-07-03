#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void addToVotes(int vote)
{
    FILE *file = fopen("votes.bin", "ab");
    if(!file)
    {
        printf("File could not be opened");
        exit(1);
    }
    fwrite(&vote, sizeof(int), 1, file);
    fclose(file);
}
void randomVotes(int peopleCount)
{
    FILE *file = fopen("votes.bin", "rb+");
    if(!file)
    {
        printf("File could not be opened");
        exit(1);
    }
    int voteCount = 0;
    int vote;
    while(fread(&vote, sizeof(int), 1, file))
    {
        voteCount++;
    }

    srand(time(NULL));

    while(voteCount<peopleCount)
    {
        int computerVote = rand() % 9 + 1;
        fwrite(&computerVote, sizeof(int), 1, file);
        voteCount++;
    }
    fclose(file);
}
void calculateVotes()
{
    FILE *file = fopen("votes.bin", "rb");
    if(!file)
    {
        printf("File could not be opened");
        exit(1);
    }
    int voteCount[9] = {0};
    int currVote;
    while(fread(&currVote, sizeof(int), 1, file))
    {
        voteCount[currVote-1]++;
    }
    for(int i = 0; i < 9; i++)
    {
        printf("Votes for %d: %d\n", i+1, voteCount[i]);
    }
    fclose(file);
}
void declareWinner()
{
    FILE *file = fopen("votes.bin", "rb");
    if(!file)
    {
        printf("File could not be opened");
        exit(1);
    }
    printf("How many people should have voted?\n");
    int people;
    scanf("%d", &people);
    randomVotes(people);
    int voteCount[9] = {0};
    int currVote;
    while(fread(&currVote, sizeof(int), 1, file))
    {
        voteCount[currVote-1]++;
    }
    int temp = 0;
    int winner = 0;
    for(int i = 0; i < 9; i++)
    {
        if(voteCount[i] > temp)
        {
            temp = voteCount[i];
            winner = i + 1;
        }
    }
    printf("The winner is %d with %d votes.", winner, temp);
    fclose(file);
}
int main()
{
    printf("Hello, please vote for your preference\n");
    printf("1)ABC   2)BCD\n3)CDE   4)DEF\n5)EFG   6)FGH\n7)GHI   8)HIJ\n9) Neutral\n");
    int vote;
    scanf("%d", &vote);
    while((vote<1 || vote>9) && vote != 123321)
    {
        printf("Invalid vote.\n");
        scanf("%d", &vote);
    }
    if(vote != 123321)
    {
        addToVotes(vote);
        printf("Thank you for voting!\n");
    }
    else
    {
        printf("Hello Admin!\n1)Calculate votes\n2)Declare Winner\n");
        int choice = 0;
        scanf("%d", &choice);
        while(choice <1 || choice > 2)
        {
            printf("Invalid choice");
            scanf("%d", &choice);
        }
        if(choice == 1)
        {
            calculateVotes();
        }
        else
        {
            declareWinner();
            printf("\nDo you want to see the results?(1=Y/0=N)\n");
            int choice = 0;
            scanf("%d", &choice);
            while(choice != 0 && choice != 1)
            {
                scanf("%d", &choice);
            }
            if(choice == 1)
            {
                calculateVotes();
            }
        }
    }
    return 0;
}
