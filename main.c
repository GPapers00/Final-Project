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

void initialize_profile(SleepTracker *tracker);
void record_sleep_session(HealthMetrics *passing_health, SleepTracker *tracker);
void analyze_sleep_patterns(SleepTracker *tracker);
float calculate_sleep_score(SleepTracker *tracker);
void provide_sleep_recommendations(HealthMetrics *passing_health, SleepTracker *tracker);
void check_smart_watch_availability(SleepTracker *tracker);
void input_date(Date *date);
int validate_date(Date *date);

int main() {
    SleepTracker tracker = {0};
    HealthMetrics passing_health = {0};
    int choice;

    printf("Welcome to the Advanced Sleep Tracking Program\n");

    check_smart_watch_availability(&tracker);

    initialize_profile(&tracker);

    while (1) {
        printf("\n--- Sleep Tracking Menu ---\n");
        printf("1. Record Sleep Session\n");
        printf("2. Analyze Sleep Patterns\n");
        printf("3. View Sleep Score\n");
        printf("4. Get Sleep Recommendations\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                record_sleep_session(&passing_health, &tracker);
                break;
            case 2:
                analyze_sleep_patterns(&tracker);
                break;
            case 3: {
                float sleep_score = calculate_sleep_score(&tracker);
                printf("Your Sleep Score: %.2f/100\n", sleep_score);
                break;
            }
            case 4:
                provide_sleep_recommendations(&passing_health, &tracker);
                break;
            case 5:
                printf("Exiting Sleep Tracking Program. Sleep Well!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void input_date(Date *date) {
    printf("Enter date (DD MM YYYY): ");
    scanf("%d %d %d", &date->day, &date->month, &date->year);

    while (!validate_date(date)) {
        printf("Invalid date. Please enter a valid date (DD MM YYYY): ");
        scanf("%d %d %d", &date->day, &date->month, &date->year);
    }
}

int validate_date(Date *date) {
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (date->year < 2000 || date->year > 2100)
        return 0;

    if (date->month < 1 || date->month > 12)
        return 0;

    if (date->year % 4 == 0 && (date->year % 100 != 0 || date->year % 400 == 0))
        days_in_month[1] = 29;

    if (date->day < 1 || date->day > days_in_month[date->month - 1])
        return 0;

    return 1;
}

void check_smart_watch_availability(SleepTracker *tracker) {
    char response;
    printf("Do you have a smart watch that can track heart rate and oxygen levels? (Y/N): ");
    scanf(" %c", &response);

    if (response == 'Y' || response == 'y') {
        tracker->has_smart_watch = 1;
        printf("Smart watch detected. We'll use its data for more accurate tracking.\n");
    } else {
        tracker->has_smart_watch = 0;
        printf("No smart watch detected. You'll need to manually input health metrics.\n");
    }
}

void initialize_profile(SleepTracker *tracker) {
    printf("Enter your name: ");
    scanf("%s", tracker->user.name);

    printf("Enter age: ");
    scanf("%d", &tracker->user.age);

    printf("Enter weight (kg): ");
    scanf("%f", &tracker->user.weight);

    printf("Enter height (cm): ");
    scanf("%f", &tracker->user.height);

    printf("Enter gender: ");
    scanf("%s", tracker->user.gender);

    while (1) {
        printf("Enter any chronic health conditions such as 'chronic, mental, sleep apnea, insomnia, restless legs, narcolepsy.' (or 'None'): ");
        scanf(" %199[^\n]", tracker->user.health_conditions);

        if (strcmp(tracker->user.health_conditions, "None") == 0 || strcmp(tracker->user.health_conditions, "none") == 0) {
            printf("No chronic health conditions reported.\n");
            break;
        }

        if (strstr(tracker->user.health_conditions, "chronic")) {
            printf("You mentioned 'chronic'. A chronic condition may include long-term health issues. "
                "Does this describe your condition? If yes, type 'yes', otherwise type 'no': ");
            char response[4];
            scanf(" %3s", response);
            if (strcmp(response, "yes") == 0) {
                printf("You have confirmed 'chronic'. We'll provide tips for managing chronic conditions.\n");
                break;
            } else {
                continue;
            }
        }

        if (strstr(tracker->user.health_conditions, "mental")) {
            printf("You mentioned 'mental'. A mental health condition could refer to issues such as depression, anxiety, etc. "
                "Does this describe your condition? If yes, type 'yes', otherwise type 'no': ");
            char response[4];
            scanf(" %3s", response);
            if (strcmp(response, "yes") == 0) {
                printf("You have confirmed 'mental'. We'll provide tips for managing mental health conditions.\n");
                break;
            } else {
                continue;
            }
        }

        if (strstr(tracker->user.health_conditions, "sleep apnea")) {
            printf("You mentioned 'sleep apnea'. Sleep apnea can affect breathing during sleep. "
                "Does this describe your condition? If yes, type 'yes', otherwise type 'no': ");
            char response[4];
            scanf(" %3s", response);
            if (strcmp(response, "yes") == 0) {
                printf("You have confirmed 'sleep apnea'. We'll provide tips for managing sleep apnea.\n");
                break;
            } else {
                continue;
            }
        }

        if (strstr(tracker->user.health_conditions, "insomnia")) {
            printf("You mentioned 'insomnia'. Insomnia refers to difficulty falling or staying asleep. "
                "Does this describe your condition? If yes, type 'yes', otherwise type 'no': ");
            char response[4];
            scanf(" %3s", response);
            if (strcmp(response, "yes") == 0) {
                printf("You have confirmed 'insomnia'. We'll provide tips for managing insomnia.\n");
                break;
            } else {
                continue;
            }
        }

        if (strstr(tracker->user.health_conditions, "restless legs")) {
            printf("You mentioned 'restless legs'. This condition involves an uncontrollable urge to move your legs, often at night. "
                "Does this describe your condition? If yes, type 'yes', otherwise type 'no': ");
            char response[4];
            scanf(" %3s", response);
            if (strcmp(response, "yes") == 0) {
                printf("You have confirmed 'restless legs'. We'll provide tips for managing this condition.\n");
                break;
            } else {
                continue;
            }
        }

        if (strstr(tracker->user.health_conditions, "narcolepsy")) {
            printf("You mentioned 'narcolepsy'. Narcolepsy is a sleep disorder that causes excessive daytime drowsiness. "
                "Does this describe your condition? If yes, type 'yes', otherwise type 'no': ");
            char response[4];
            scanf(" %3s", response);
            if (strcmp(response, "yes") == 0) {
                printf("You have confirmed 'narcolepsy'. We'll provide tips for managing narcolepsy.\n");
                break;
            } else {
                continue;
            }
        }

        printf("You entered a condition that doesn't match our list. Please enter a valid chronic health condition or 'None':\n");
    }

}

void record_sleep_session(HealthMetrics *passing_health, SleepTracker *tracker) {
    if (tracker->record_count >= 365) {
        printf("Cannot record more sleep data. Maximum capacity reached.\n");
        return;
    }

    SleepData *current_sleep = &tracker->sleep_record[tracker->record_count];
    HealthMetrics *current_health = &tracker->health_data[tracker->record_count];
    EnvironmentalFactors *current_env = &tracker->env_factors[tracker->record_count];

    input_date(&current_sleep->sleep_date);

    printf("Enter sleep start time (hour minute, 24-hour format): ");
    scanf("%d %d", &current_sleep->start_hour, &current_sleep->start_minute);

    printf("Enter sleep end time (hour minute, 24-hour format): ");
    scanf("%d %d", &current_sleep->end_hour, &current_sleep->end_minute);

    int start_time_in_minutes = current_sleep->start_hour * 60 + current_sleep->start_minute;
    int end_time_in_minutes = current_sleep->end_hour * 60 + current_sleep->end_minute;

    if (end_time_in_minutes < start_time_in_minutes) {
        end_time_in_minutes += 24 * 60;
    }

    int total_sleep_duration_minutes = end_time_in_minutes - start_time_in_minutes;

    current_sleep->total_sleep_duration = total_sleep_duration_minutes / 60.0;

    printf("Enter REM sleep duration (minutes): ");
    scanf("%d", &current_sleep->rem_sleep_duration);

    printf("Enter Deep sleep duration (minutes): ");
    scanf("%d", &current_sleep->deep_sleep_duration);

    current_sleep->light_sleep_duration = 
        (int)(current_sleep->total_sleep_duration * 60) - 
        (current_sleep->rem_sleep_duration + current_sleep->deep_sleep_duration);

    if (tracker->has_smart_watch) {
        printf("Retrieving health data from smart watch...\n");
        int min, max;

        static int seeded = 0;
        if (!seeded) {
            srand(time(NULL));
            seeded = 1;
        }

        if (tracker->user.age >= 0 && tracker->user.age <= 2) {
            min = 80; max = 130;
        } else if (tracker->user.age >= 3 && tracker->user.age <= 4) {
            min = 80; max = 120;
        } else if (tracker->user.age >= 5 && tracker->user.age <= 6) {
            min = 75; max = 115;
        } else if (tracker->user.age >= 7 && tracker->user.age <= 9) {
            min = 70; max = 110;
        } else if (tracker->user.age >= 10 && tracker->user.age <= 15) {
            min = 60; max = 100;
        } else {
            min = 60; max = 99;
        }

        passing_health->heart_rate = (rand() % (max - min + 1)) + min;

        min = 60; max = 100;
        passing_health->oxygen_level = (rand() % (max - min + 1)) + min;

        printf("Detected Resting Heart Rate : %.0f bpm\n", passing_health->heart_rate);
        printf("Detected Oxygen Level : %.0f %%\n", passing_health->oxygen_level);

        current_health->heart_rate = passing_health->heart_rate;
        current_health->oxygen_level = passing_health->oxygen_level;

    } else {
        passing_health->heart_rate = 0;
        passing_health->oxygen_level = 0;

        current_health->heart_rate = passing_health->heart_rate;
        current_health->oxygen_level = passing_health->oxygen_level;
    }

    current_health->heart_rate = passing_health->heart_rate;
    current_health->oxygen_level = passing_health->oxygen_level;

    printf("Enter breathing rate (breaths per minute): ");
    scanf("%d", &current_health->breathing_rate);

    printf("Enter environmental noise level: ");
    scanf("%f", &current_env->noise_level);

    printf("Enter room temperature: ");
    scanf("%f", &current_env->room_temperature);

    tracker->record_count++;
}


void analyze_sleep_patterns(SleepTracker *tracker) {
    if (tracker->record_count == 0) {
        printf("No sleep data recorded yet.\n");
        return;
    }

    float total_sleep = 0, total_rem = 0, total_deep = 0;
    for (int i = 0; i < tracker->record_count; i++) {
        total_sleep += tracker->sleep_record[i].total_sleep_duration;
        total_rem += tracker->sleep_record[i].rem_sleep_duration;
        total_deep += tracker->sleep_record[i].deep_sleep_duration;
    }

    printf("\n--- Sleep Pattern Analysis ---\n");
    printf("Average Total Sleep: %.2f hours\n", total_sleep / tracker->record_count);
    printf("Average REM Sleep: %.2f minutes\n", total_rem / tracker->record_count);
    printf("Average Deep Sleep: %.2f minutes\n", total_deep / tracker->record_count);
}

float calculate_sleep_score(SleepTracker *tracker) {
    if (tracker->record_count == 0) return 0;

    SleepData *latest_sleep = &tracker->sleep_record[tracker->record_count - 1];
    HealthMetrics *latest_health = &tracker->health_data[tracker->record_count - 1];

    float score = 0;

    if (latest_sleep->total_sleep_duration >= 7 && latest_sleep->total_sleep_duration <= 9)
        score += 40;
    else
        score += (40 * (1 - abs(latest_sleep->total_sleep_duration - 8) / 2));

    score += (latest_sleep->deep_sleep_duration / 60.0) * 30;
    score += (latest_sleep->rem_sleep_duration / 60.0) * 20;

    if(tracker->has_smart_watch) {
        if (latest_health->heart_rate >= 60 && latest_health->heart_rate <= 100) {
            score += 10;
        }
    }

    if (strstr(tracker->user.health_conditions, "chronic") || strstr(tracker->user.health_conditions, "mental") || strstr(tracker->user.health_conditions, "sleep apnea") || strstr(tracker->user.health_conditions, "insomnia") || strstr(tracker->user.health_conditions, "restless legs") || strstr(tracker->user.health_conditions, "narcolepsy")) {
        printf("Health conditions detected: Adjusting sleep score slightly.\n");
        score -= 5;
    }

    return (score > 100) ? 100 : score;
}

void provide_sleep_recommendations(HealthMetrics *passing_health, SleepTracker *tracker) {
    float sleep_score = calculate_sleep_score(tracker);

    printf("\n--- Sleep Recommendations ---\n");

    printf("General Tips:\n");
    printf("- Maintain a consistent sleep schedule.\n");
    printf("- Optimize your sleep environment.\n");
    printf("- Avoid caffeine and screens before bedtime.\n");

    if (sleep_score < 50) {
        printf("Critical Improvement Needed: Seek professional advice if issues persist.\n");
    } else if (sleep_score < 75) {
        printf("Moderate Improvement Needed: Focus on sleep hygiene and relaxation techniques.\n");
    } else {
        printf("Good Sleep Quality: Keep up the healthy habits!\n");
    }

    if (strstr(tracker->user.health_conditions, "chronic")) {
        printf("Specific Tip: Ensure your chronic condition is well-managed as it can impact sleep.\n");
    } else if (strstr(tracker->user.health_conditions, "mental")) {
        printf("Specific Tip: Ensure your mental health condition is well-managed as it can impact sleep.\n");
    } else if (strstr(tracker->user.health_conditions, "sleep apnea")) {
        printf("Specific Tip: If you have sleep apnea, consider seeking treatment to improve sleep quality.\n");
    } else if (strstr(tracker->user.health_conditions, "insomnia")) {
        printf("Specific Tip: Manage insomnia by establishing a consistent sleep routine and reducing stress.\n");
    } else if (strstr(tracker->user.health_conditions, "restless legs")) {
        printf("Specific Tip: Address restless legs syndrome to reduce sleep disturbances.\n");
    } else if (strstr(tracker->user.health_conditions, "narcolepsy")) {
        printf("Specific Tip: If you have narcolepsy, try to manage your sleep schedule to prevent excessive daytime sleepiness.\n");
    } else {
        printf("Specific Tip: Monitor your health conditions as they can all affect sleep.\n");
    }

    if (passing_health->oxygen_level >= 96 && passing_health->oxygen_level <= 100) {
        printf("Your oxygen level is on the green zone. Normal oxygen level, maintain a healthy lifestyle.\n");
    } else if (passing_health->oxygen_level >= 91 && passing_health->oxygen_level <= 95) {
        printf("Your oxygen level is on the yellow zone. Concerning oxygen level, do breathing exercises and improve air quality.\n");
    } else if (passing_health->oxygen_level >= 80 && passing_health->oxygen_level <= 90) {
        printf("Your oxygen level is on the orange zone. Low oxygen level, seek medical advice and consider supplemental oxygen.\n");
    } else if (passing_health->oxygen_level >= 76 && passing_health->oxygen_level <= 79) {
        printf("Your oxygen level is on the red zone. Critical oxygen level, seek emergency medical help immediately.\n");
    } else if (passing_health->oxygen_level >= 60 && passing_health->oxygen_level <= 75) {
        printf("Cyanosis detected, please seek for professional doctor's help urgently.\n");
    } else {
        return;
    }

}
