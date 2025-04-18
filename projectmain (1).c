#include <stdio.h>
#include <string.h>
#include "project.h"

int main(void)
{
    char season[MAX_SEASON_LENGTH];
    char eventName[MAX_EVENT_NAME_LENGTH];
    int year;

    printf("Enter Olympic year (e.g., 2000): ");
    scanf("%d", &year);
    while (getchar() != '\n');

    printf("Enter season (Summer or Winter): ");
    fgets(season, MAX_SEASON_LENGTH, stdin);
    season[strcspn(season, "\n")] = 0;

    printf("Enter event name (case-sensitive, exact): ");
    fgets(eventName, MAX_EVENT_NAME_LENGTH, stdin);
    eventName[strcspn(eventName, "\n")] = 0;

    int count = countParticipants("Olympic_Athlete_Event_Results.csv", year, season, eventName);

    if (count >= 0) {
        printf("Number of unique athletes in %s %d %s: %d\n", season, year, eventName, count);
    } else {
        printf("An error occurred during processing.\n");
    }

    return 0;
}
