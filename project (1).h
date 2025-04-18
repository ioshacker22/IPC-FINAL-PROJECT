#ifndef PROJECT_H
#define PROJECT_H

#define MAX_LINE_LENGTH 1024
#define MAX_EVENT_NAME_LENGTH 100
#define MAX_SEASON_LENGTH 10
#define MAX_FILENAME_LENGTH 100
#define MAX_ATHLETES 10000

struct AthleteEntry {
    int id;
    char event[MAX_EVENT_NAME_LENGTH];
    int year;
    char season[MAX_SEASON_LENGTH];
};

int countParticipants(const char* filename, int year, const char* season, const char* eventName);

#endif
