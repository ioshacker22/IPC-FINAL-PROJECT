#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "project.h"

void trim(char *str) {
    if (str == NULL) return;
    char *start = str;
    while (isspace((unsigned char)*start)) start++;
    if (*start == 0) {
        *str = 0;
        return;
    }
    char *end = str + strlen(str) - 1;
    while (end > start && isspace((unsigned char)*end)) end--;
    *(end + 1) = 0;
    if (start != str) {
        memmove(str, start, strlen(start) + 1);
    }
}

int countParticipants(const char* filename, int year, const char* season, const char* eventName) {
    int uniqueCount = 0;
    int athleteIds[MAX_ATHLETES] = {0};
    char line[MAX_LINE_LENGTH];

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return -1;
    }
    
    if (fgets(line, MAX_LINE_LENGTH, file) == NULL) {
        fclose(file);
        return -1;
    }
    
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        char lineCopy[MAX_LINE_LENGTH];
        strncpy(lineCopy, line, MAX_LINE_LENGTH - 1);
        lineCopy[MAX_LINE_LENGTH - 1] = '\0';

        int colIndex = 0;
        int yearFromFile = 0;
        char seasonFromFile[MAX_SEASON_LENGTH] = {0};
        char eventFromFile[MAX_EVENT_NAME_LENGTH] = {0};
        int athleteId = 0;
        char *ptr = lineCopy;
        char field[MAX_LINE_LENGTH];
        int fieldPos = 0;
        int inQuotes = 0;

        while (*ptr && colIndex < 8) {
            if (*ptr == '"') {
                inQuotes = !inQuotes;
                ptr++;
                continue;
            }
            if (*ptr == ',' && !inQuotes) {
                field[fieldPos] = '\0';
                if (colIndex == 0) {
                    yearFromFile = atoi(field);
                    if (strstr(field, "Summer") != NULL) strcpy(seasonFromFile, "Summer");
                    else if (strstr(field, "Winter") != NULL) strcpy(seasonFromFile, "Winter");
                } else if (colIndex == 4) {
                    strncpy(eventFromFile, field, MAX_EVENT_NAME_LENGTH - 1);
                    eventFromFile[MAX_EVENT_NAME_LENGTH - 1] = '\0';
                    trim(eventFromFile);
                } else if (colIndex == 7) {
                    athleteId = atoi(field);
                }
                colIndex++;
                fieldPos = 0;
                ptr++;
                continue;
            }
            if (fieldPos < MAX_LINE_LENGTH - 1) {
                field[fieldPos++] = *ptr;
            }
            ptr++;
        }
        if (fieldPos > 0) {
            field[fieldPos] = '\0';
            if (colIndex == 7) {
                athleteId = atoi(field);
            }
            colIndex++;
        }
        
        if (colIndex < 8) {
            continue;
        }
        
        if (yearFromFile == year && 
            strcmp(seasonFromFile, season) == 0 &&
            strcmp(eventFromFile, eventName) == 0) {
            int found = 0;
            for (int i = 0; i < uniqueCount; i++) {
                if (athleteIds[i] == athleteId) {
                    found = 1;
                    break;
                }
            }
            if (!found && uniqueCount < MAX_ATHLETES) {
                athleteIds[uniqueCount++] = athleteId;
            }
        }
    }
    
    fclose(file);
    return uniqueCount;
}
