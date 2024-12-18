#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char name[50];
    int age;
    float weight;
    float height;
    char gender[10];
    char health_conditions[200];
} UserProfile;

typedef struct {
    Date sleep_date;
    int start_hour;
    int start_minute;
    int end_hour;
    int end_minute;
    float total_sleep_duration;
    int rem_sleep_duration;
    int deep_sleep_duration;
    int light_sleep_duration;
} SleepData;

typedef struct {
    float heart_rate;
    float oxygen_level;
    int breathing_rate;
    int sleep_disruptions;
} HealthMetrics;

typedef struct {
    float noise_level;
    float room_temperature;
    float light_exposure;
} EnvironmentalFactors;

typedef struct {
    UserProfile user;
    SleepData sleep_record[365];
    HealthMetrics health_data[365];
    EnvironmentalFactors env_factors[365];
    int record_count;
    int has_smart_watch;
} SleepTracker;
