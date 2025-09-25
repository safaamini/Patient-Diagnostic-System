//Made by: Amini Safa - Groupe: 05
//Patient Diagnostic System
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct for a date (day, month, year)
typedef struct Date {
    int day;    // Day of the date
    int month;  // Month of the date
    int year;   // Year of the date
} Date;

// Define an enum for diagnosis
typedef enum Diagnosis {
    Hypertension,
    Type_1Diabetes,
    Type_2Diabetes,
    Traffic_Accidents_Injuries,
    Acute_Chronic_Infections,
    Cardiovascular_Diseases,
    Cancerous_Tumors,
    Respiratory_Conditions,
    Mental_Health_Disorders,
    OTHER_DIAGNOSTIC,  // Additional diagnostic option
} Diagnosis;

// Define an enum for doctor's specialty
typedef enum Specialty {
    GENERAL_MEDICINE,
    PEDIATRICS,
    CARDIOLOGY,
    ONCOLOGY,
    NEUROLOGY,
    ORTHOPEDICS,
    SURGERY,
    OTHER_SPECIALTY  // Additional specialty option
} Specialty;

// Define a struct for a patient record
typedef struct Patient {
    int patientID;          // Unique identifier for the patient
    char fullName[50];      // Patient's full name
    int age;                // Patient's age
    char gender;            // Patient's gender
    float height;           // Patient's height in meters
    struct Patient *next;   // Pointer to the next patient in a linked list
} Patient;

// Define a struct for a diagnostic record
typedef struct Diagnostic {
    int patientID;                // Unique identifier for the patient
    int doctorID;                 // Unique identifier for the doctor
    Diagnosis diagnosis;          // Type of diagnosis
    char OtherDiagnosis[50];      // Additional diagnosis if OTHER_DIAGNOSTIC is selected
    Date diagDate;                // Date of diagnosis
    Date nextAppointment;         // Date of the next appointment
    struct Diagnostic *next;      // Pointer to the next diagnostic record
} Diagnostic;

// Define a struct for a doctor record
typedef struct Doctor {
    int doctorID;               // Unique identifier for the doctor
    char fullNameDoc[50];      // Doctor's full name
    Specialty specialty;       // Doctor's specialty
    char OtherSpecialty[50];   // Additional specialty (if OTHER_SPECIALTY is chosen)
    Diagnostic *diagnosticList;    // List of diagnostics performed by the doctor
    struct Doctor *next;       // Pointer to the next doctor in a linked list
} Doctor;

// Global variable for patient list
Patient *patientList = NULL;

// Global variable for diagnostic list
Diagnostic *diagnosticList = NULL;

// Global variable for doctor list
Doctor *doctorList = NULL;

// Function to add a new patient to the patientList
void add_patient() {
    // Allocate memory for a new patient node
    Patient *new_patient = (Patient *)malloc(sizeof(Patient));
    if (new_patient == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    // Input validation for patient ID (positive value)
    do {
        printf("Enter patient ID: ");
        scanf("%d", &new_patient->patientID);
        if (new_patient->patientID <= 0) {
            printf("Invalid ID. Please enter a positive integer.\n");
        }
    } while (new_patient->patientID <= 0);

    // Check if patient ID already exists
    Patient *current = patientList;
    while (current != NULL) {
        if (current->patientID == new_patient->patientID) {
            printf("Patient ID already exists. Please enter a different ID.\n");
            free(new_patient); // Free memory if ID already exists
            return;
        }
        current = current->next;
    }

    while (getchar() != '\n');

    // Get patient information
    printf("Enter patient full name: ");
    fgets(new_patient->fullName, sizeof(new_patient->fullName), stdin);
    strtok(new_patient->fullName, "\n"); // Remove trailing newline character

    // Input validation for age (positive value)
    do {
        printf("Enter patient age: ");
        scanf("%d", &new_patient->age);
        if (new_patient->age <= 0) {
            printf("Invalid age. Please enter a positive integer.\n");
        }
    } while (new_patient->age <= 0);

    // Input validation for gender (M/F)
    do {
        printf("Enter patient gender (M/F): ");
        scanf(" %c", &new_patient->gender);
        if (new_patient->gender != 'M' && new_patient->gender != 'F') {
            printf("Invalid gender. Please enter 'M' for male or 'F' for female.\n");
        }
    } while (new_patient->gender != 'M' && new_patient->gender != 'F');

    // Input validation for height (positive value)
    do {
        printf("Enter patient height (in meters): ");
        scanf("%f", &new_patient->height);
        if (new_patient->height <= 0) {
            printf("Invalid height. Please enter a positive number.\n");
        }
    } while (new_patient->height <= 0);

    // Insert new patient at the beginning of the linked list
    new_patient->next = patientList;
    patientList = new_patient;

    printf("Patient added successfully.\n");
}

// Function to update patient information based on patient ID
void update_patient() {
    int patientID;

    // Input validation for patient ID (positive value)
    do {
        printf("Enter patient ID: ");
        scanf("%d", &patientID);
        if (patientID <= 0) {
            printf("Invalid ID. Please enter a positive integer.\n");
        }
    } while (patientID <= 0);

    // Search for the patient by ID
    Patient *current = patientList;
    while (current != NULL) {
        if (current->patientID == patientID) {
            // Update patient information
            printf("Enter updated full name: ");
            getchar(); // Clear the newline character from the buffer
            fgets(current->fullName, sizeof(current->fullName), stdin);
            strtok(current->fullName, "\n"); // Remove trailing newline character

            // Input validation for age (positive integer)
            do {
                printf("Enter updated age: ");
                scanf("%d", &current->age);
                if (current->age <= 0) {
                    printf("Invalid age. Please enter a positive integer.\n");
                }
            } while (current->age <= 0);

            // Input validation for gender (M/F)
            do {
        printf("Enter updated gender (M/F): ");
        scanf(" %c", &current->gender);
        if (current->gender != 'M' && current->gender != 'F') {
            printf("Invalid gender. Please enter 'M' for male or 'F' for female.\n");
        }
    } while (current->gender != 'M' && current->gender != 'F');

            // Input validation for height (positive number)
            do {
                printf("Enter updated height (in meters): ");
                scanf("%f", &current->height);
                if (current->height <= 0) {
                    printf("Invalid height. Please enter a positive number.\n");
                }
            } while (current->height <= 0);

            printf("Patient record updated successfully.\n");
            return;
        }
        current = current->next;
    }

    printf("Patient not found.\n");
}

// Function to delete a patient by patient ID
void delete_patient() {
    int patientID;

    // Input validation for patient ID (positive value)
    do {
        printf("Enter patient ID to delete: ");
        scanf("%d", &patientID);
        if (patientID <= 0) {
            printf("Invalid ID. Please enter a positive integer.\n");
        }
    } while (patientID <= 0);

    // Search for the patient by ID
    Patient *current = patientList;
    Patient *prev = NULL; // Pointer to the previous node

    while (current != NULL) {
        if (current->patientID == patientID) {
            // Handle deletion based on node position
            if (prev == NULL) { // Deleting the head node
                patientList = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Patient deleted successfully.\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Patient not found.\n");
}

// Function to search for a patient by name
void search_patient() {
    char searchName[50];

    // Input patient name to search
    printf("Enter patient name to search: ");
    scanf("%s", searchName);

    Patient *current = patientList;
    int found = 0;
    while (current != NULL) {
        // Compare the entered name with the name in the current patient record
        if (strstr(current->fullName, searchName) != NULL) {
            printf("Patient found:\n");
            printf("Patient ID: %d\n", current->patientID);
            printf("Full Name: %s\n", current->fullName);
            printf("Age: %d\n", current->age);
            printf("Gender: %c\n", current->gender);
            printf("Height: %.2f meters\n", current->height);
            printf("-------------------------\n");

            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No patients found with the name '%s'.\n", searchName);
    }
}

// Function to print patient information based on patient ID
void print_patient() {
    int patientID;

    // Check if the linked list is empty
    if (patientList == NULL) {
        printf("No patients found.\n");
        return;
    }

    // Input validation for patient ID (positive value)
    do {
        printf("Enter patient ID to print: ");
        scanf("%d", &patientID);
        if (patientID <= 0) {
            printf("Invalid ID. Please enter a positive integer.\n");
        }
    } while (patientID <= 0);

    // Traverse the linked list to find the patient with the given ID
    Patient *current = patientList;
    while (current != NULL) {
        if (current->patientID == patientID) {
            printf("Patient information:\n");
            printf("Patient ID: %d\n", current->patientID);
            printf("Full Name: %s\n", current->fullName);
            printf("Age: %d\n", current->age);
            printf("Gender: %c\n", current->gender);
            printf("Height: %.2f meters\n", current->height);
            return; // Exit the function after printing the patient's information
        }
        current = current->next; // Move to the next node in the linked list
    }
    printf("Patient not found.\n"); // If the patient ID is not found in the linked list
}

// Function to free allocated memory for the linked list
void free_patient_memory() {
    Patient *current = patientList; // Start from the head of the linked list

    // Traverse the linked list and free memory for each node
    while (current != NULL) {
        Patient *temp = current; // Store the current node in a temporary variable
        current = current->next; // Move to the next node
        free(temp); // Free memory for the current node
    }
}

// Function to check if a date is valid
int is_valid_date(Date date) {
    // Basic validation for simplicity
    if (date.year < 1900 || date.month < 1 || date.month > 12 || date.day < 1 || date.day > 31) {
        return 0; // Return false if any condition fails
    }
    return 1; // Return true if all conditions pass
}

// Function to check if date1 is before date2
int is_before_date(Date date1, Date date2) {
    // Compare years
    if (date1.year < date2.year) {
        return 1;
    }
    // If years are equal, compare months
    else if (date1.year == date2.year) {
        if (date1.month < date2.month) {
            return 1;
        }
        // If months are equal, compare days
        else if (date1.month == date2.month) {
            if (date1.day < date2.day) {
                return 1;
            }
        }
    }
    // date1 is not before date2
    return 0;
}

// Function to add a new diagnostic record
void add_diagnostic() {
    Diagnostic *new_diagnostic = (Diagnostic *)malloc(sizeof(Diagnostic));
    if (new_diagnostic == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    // Input validation for patient ID (positive value)
    do {
        printf("Enter patient ID: ");
        scanf("%d", &new_diagnostic->patientID);
        if (new_diagnostic->patientID <= 0) {
            printf("Invalid ID. Please enter a positive integer.\n");
        }
    } while (new_diagnostic->patientID <= 0);

    // Input validation for doctor ID (positive value)
    do {
        printf("Enter doctor ID: ");
        scanf("%d", &new_diagnostic->doctorID);
        if (new_diagnostic->doctorID <= 0) {
            printf("Invalid ID. Please enter a positive integer.\n");
        }
    } while (new_diagnostic->doctorID <= 0);

    // Check if patient ID and doctor ID exist
    Patient *patient_current = patientList;
    Doctor *doctor_current = doctorList;
    int patient_found = 0, doctor_found = 0;

    while (patient_current != NULL) {
        if (patient_current->patientID == new_diagnostic->patientID) {
            patient_found = 1;
            break;
        }
        patient_current = patient_current->next;
    }

    while (doctor_current != NULL) {
        if (doctor_current->doctorID == new_diagnostic->doctorID) {
            doctor_found = 1;
            break;
        }
        doctor_current = doctor_current->next;
    }

    // If patient or doctor not found, free memory and return
    if (!patient_found || !doctor_found) {
        printf("Patient or Doctor not found.\n");
        free(new_diagnostic);
        return;
    }

    // Input for diagnosis type
    printf("Select diagnostic:\n");
    printf("0: Hypertension\n");
    printf("1: Type 1 Diabetes\n");
    printf("2: Type 2 Diabetes\n");
    printf("3: Traffic Accidents Injuries\n");
    printf("4: Acute Chronic Infections\n");
    printf("5: Cardiovascular Diseases\n");
    printf("6: Cancerous Tumors\n");
    printf("7: Respiratory Conditions\n");
    printf("8: Mental Health Disorders\n");
    printf("9: Other Diagnostic\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);

    if (choice == OTHER_DIAGNOSTIC) {
        printf("Enter the diagnostic: ");
        while (getchar() != '\n'); // Clear input buffer
        fgets(new_diagnostic->OtherDiagnosis, sizeof(new_diagnostic->OtherDiagnosis), stdin);
        strtok(new_diagnostic->OtherDiagnosis, "\n"); // Remove newline character
        new_diagnostic->diagnosis = OTHER_DIAGNOSTIC;
    } else if (choice >= Hypertension && choice <= Mental_Health_Disorders) {
        new_diagnostic->diagnosis = (Diagnosis)choice;
        new_diagnostic->OtherDiagnosis[0] = '\0'; // Clear custom diagnostic
    } else {
        printf("Invalid choice. Setting diagnostic to Other.\n");
        new_diagnostic->diagnosis = OTHER_DIAGNOSTIC;
        new_diagnostic->OtherDiagnosis[0] = '\0';
    }

    // Input validation for diagnosis date
    do {
        printf("Enter diagnosis date (DD MM YYYY): ");
        scanf("%d %d %d", &new_diagnostic->diagDate.day, &new_diagnostic->diagDate.month, &new_diagnostic->diagDate.year);
        if (!is_valid_date(new_diagnostic->diagDate)) {
            printf("Invalid date. Please enter a valid date.\n");
        }
    } while (!is_valid_date(new_diagnostic->diagDate));

    // Input validation for next appointment date
    do {
        printf("Enter next appointment date (DD MM YYYY): ");
        scanf("%d %d %d", &new_diagnostic->nextAppointment.day, &new_diagnostic->nextAppointment.month, &new_diagnostic->nextAppointment.year);
        if (!is_valid_date(new_diagnostic->nextAppointment) || is_before_date(new_diagnostic->nextAppointment, new_diagnostic->diagDate)) {
            printf("Invalid date or next appointment date cannot be before diagnosis date. Please enter a valid date.\n");
        }
    } while (!is_valid_date(new_diagnostic->nextAppointment) || is_before_date(new_diagnostic->nextAppointment, new_diagnostic->diagDate));

    // Insert new diagnostic record at the beginning of the linked list
    new_diagnostic->next = diagnosticList;
    diagnosticList = new_diagnostic;

    printf("Diagnostic record added successfully.\n");
}

// Function to update an existing diagnostic record
void update_diagnostic() {
    int patientID, doctorID;

    // Input validation for patient ID (positive value)
    do {
        printf("Enter patient ID: ");
        scanf("%d", &patientID);
        if (patientID <= 0) {
            printf("Invalid ID. Please enter a positive integer.\n");
        }
    } while (patientID <= 0);

    // Input validation for doctor ID (positive value)
    do {
        printf("Enter doctor ID: ");
        scanf("%d", &doctorID);
        if (doctorID <= 0) {
            printf("Invalid ID. Please enter a positive integer.\n");
        }
    } while (doctorID <= 0);

    Diagnostic *current = diagnosticList;
    Diagnostic *to_update = NULL;

    // Search for the diagnostic record
    while (current != NULL) {
        if (current->patientID == patientID && current->doctorID == doctorID) {
            to_update = current;
            break;
        }
        current = current->next;
    }

    if (to_update == NULL) {
        printf("Diagnostic record not found.\n");
        return;
    }

    // Input for diagnosis type
    printf("Select updated diagnostic:\n");
    printf("0: Hypertension\n");
    printf("1: Type 1 Diabetes\n");
    printf("2: Type 2 Diabetes\n");
    printf("3: Traffic Accidents Injuries\n");
    printf("4: Acute Chronic Infections\n");
    printf("5: Cardiovascular Diseases\n");
    printf("6: Cancerous Tumors\n");
    printf("7: Respiratory Conditions\n");
    printf("8: Mental Health Disorders\n");
    printf("9: Other Diagnostic\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);

    if (choice == OTHER_DIAGNOSTIC) {
        printf("Enter the diagnostic: ");
        while (getchar() != '\n'); // Clear input buffer
        fgets(to_update->OtherDiagnosis, sizeof(to_update->OtherDiagnosis), stdin);
        strtok(to_update->OtherDiagnosis, "\n"); // Remove newline character
        to_update->diagnosis = OTHER_DIAGNOSTIC;
    } else if (choice >= Hypertension && choice <= Mental_Health_Disorders) {
        to_update->diagnosis = (Diagnosis)choice;
        to_update->OtherDiagnosis[0] = '\0'; // Clear custom diagnostic
    } else {
        printf("Invalid choice. Setting diagnostic to Other.\n");
        to_update->diagnosis = OTHER_DIAGNOSTIC;
        to_update->OtherDiagnosis[0] = '\0';
    }

    // Input validation for diagnosis date
    do {
        printf("Enter updated diagnosis date (DD MM YYYY): ");
        scanf("%d %d %d", &to_update->diagDate.day, &to_update->diagDate.month, &to_update->diagDate.year);
        if (!is_valid_date(to_update->diagDate)) {
            printf("Invalid date. Please enter a valid date.\n");
        }
    } while (!is_valid_date(to_update->diagDate));

    // Input validation for next appointment date
    do {
        printf("Enter updated next appointment date (DD MM YYYY): ");
        scanf("%d %d %d", &to_update->nextAppointment.day, &to_update->nextAppointment.month, &to_update->nextAppointment.year);
        if (!is_valid_date(to_update->nextAppointment) || is_before_date(to_update->nextAppointment, to_update->diagDate)) {
            printf("Invalid date or next appointment date cannot be before diagnosis date. Please enter a valid date.\n");
        }
    } while (!is_valid_date(to_update->nextAppointment) || is_before_date(to_update->nextAppointment, to_update->diagDate));

    printf("Diagnostic record updated successfully.\n");
}

// Function to delete a diagnostic record
void delete_diagnostic() {
    int patientID, doctorID;

    printf("Enter patient ID: ");
    scanf("%d", &patientID);
    printf("Enter doctor ID: ");
    scanf("%d", &doctorID);

    Diagnostic *current = diagnosticList;
    Diagnostic *previous = NULL;

    // Search for the diagnostic record
    while (current != NULL) {
        if (current->patientID == patientID && current->doctorID == doctorID) {
            // Found the diagnostic record
            if (previous == NULL) {
                // The record to delete is the first in the list
                diagnosticList = current->next;
            } else {
                // The record to delete is in the middle or end of the list
                previous->next = current->next;
            }
            free(current);
            printf("Diagnostic record deleted successfully.\n");
            return;
        }
        previous = current;
        current = current->next;
    }

    // If the record was not found
    printf("Diagnostic record not found.\n");
}

// Function to search for a diagnostic record
void search_diagnostic() {
    Diagnosis search_diagnosis;

    // Input for diagnosis type
    printf("Enter diagnosis to search:\n");
    printf("0: Hypertension\n");
    printf("1: Type 1 Diabetes\n");
    printf("2: Type 2 Diabetes\n");
    printf("3: Traffic Accidents Injuries\n");
    printf("4: Acute Chronic Infections\n");
    printf("5: Cardiovascular Diseases\n");
    printf("6: Cancerous Tumors\n");
    printf("7: Respiratory Conditions\n");
    printf("8: Mental Health Disorders\n");
    printf("9: Other Diagnostic\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);

    if (choice < Hypertension || choice > OTHER_DIAGNOSTIC) {
        printf("Invalid choice. Please enter a valid option.\n");
        return;
    }

    if (choice == OTHER_DIAGNOSTIC) {
        char otherDiagnosis[100];
        printf("Enter the specific diagnostic to search for: ");
        scanf(" %[^\n]%*c", otherDiagnosis);

        // Traverse the diagnostic records linked list to find matching diagnosis
        Diagnostic *current = diagnosticList;
        int found = 0;

        while (current != NULL) {
            if (current->diagnosis == OTHER_DIAGNOSTIC && strcmp(current->OtherDiagnosis, otherDiagnosis) == 0) {
                printf("\nDiagnostic record found:\n");
                printf("Patient ID: %d\n", current->patientID);
                printf("Doctor ID: %d\n", current->doctorID);
                printf("Diagnosis: %s\n", current->OtherDiagnosis);

                // Print diagnosis date and next appointment date
                printf("Diagnosis Date: %02d-%02d-%04d\n", current->diagDate.day, current->diagDate.month, current->diagDate.year);
                printf("Next Appointment: %02d-%02d-%04d\n", current->nextAppointment.day, current->nextAppointment.month, current->nextAppointment.year);
                found = 1;
            }
            current = current->next; // Move to the next diagnostic record
        }

        if (!found) {
            printf("Diagnostic record not found for the specified diagnosis.\n");
        }
    } else {
        search_diagnosis = (Diagnosis)choice;

        // Traverse the diagnostic records linked list to find matching diagnosis
        Diagnostic *current = diagnosticList;
        int found = 0;

        while (current != NULL) {
            if (current->diagnosis == search_diagnosis) {
                printf("\nDiagnostic record found:\n");
                printf("Patient ID: %d\n", current->patientID);
                printf("Doctor ID: %d\n", current->doctorID);
                if (current->diagnosis == OTHER_DIAGNOSTIC) {
                    printf("Diagnosis: %s\n", current->OtherDiagnosis);
                } else {
                    printf("Diagnosis: %d\n", current->diagnosis);
                }

                // Print diagnosis date and next appointment date
                printf("Diagnosis Date: %02d-%02d-%04d\n", current->diagDate.day, current->diagDate.month, current->diagDate.year);
                printf("Next Appointment: %02d-%02d-%04d\n", current->nextAppointment.day, current->nextAppointment.month, current->nextAppointment.year);
                found = 1;
            }
            current = current->next; // Move to the next diagnostic record
        }

        if (!found) {
            printf("Diagnostic record not found for the specified diagnosis.\n");
        }
    }
}

// Function to print diagnostic records for a specific patient
void print_diagnostic() {
    int patientID;

    // Input patient ID to search
    do {
        printf("Enter patient ID to print diagnostics: ");
        scanf("%d", &patientID);

        if (patientID <= 0) {
            printf("Invalid ID. Please enter a positive integer.\n");
        }
    } while (patientID <= 0);

    // Check if diagnostic records exist
    if (diagnosticList == NULL) {
        printf("No diagnostic records found.\n");
        return;
    }

    // Traverse the diagnostic records linked list to find records for the specified patient
    Diagnostic *current = diagnosticList;
    int found = 0;
    while (current != NULL) {
        if (current->patientID == patientID) {
            found = 1;
            printf("Diagnostic record found:\n");
            printf("Patient ID: %d\n", current->patientID);
            printf("Doctor ID: %d\n", current->doctorID);
            if (current->diagnosis == OTHER_DIAGNOSTIC) {
                printf("Diagnosis: %s\n", current->OtherDiagnosis);
            } else {
                printf("Diagnosis: %d\n", current->diagnosis);
            }
            // Print diagnosis date and next appointment date
            printf("Diagnosis Date: %d-%d-%d\n", current->diagDate.day, current->diagDate.month, current->diagDate.year);
            printf("Next Appointment: %d-%d-%d\n", current->nextAppointment.day, current->nextAppointment.month, current->nextAppointment.year);
        }
        current = current->next; // Move to the next diagnostic record
    }

    // Print message if no diagnostic records found for the specified patient ID
    if (!found) {
        printf("No diagnostic records found for patient with ID %d.\n", patientID);
    }
}

// Function to deallocate memory allocated for the diagnostic linked list
void free_diagnostic_memory() {
    Diagnostic *current = diagnosticList;
    while (current != NULL) {
        Diagnostic *temp = current;
        current = current->next;
        free(temp); // Freeing memory for the current node
    }
    diagnosticList = NULL; // Resetting the head pointer to NULL after freeing all memory
}

// Function to add a new doctor
void add_doctor() {
    // Allocate memory for a new doctor node
    Doctor *new_doctor = (Doctor *)malloc(sizeof(Doctor));
    if (new_doctor == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    // Input validation for doctor ID (positive value)
    do {
        printf("Enter doctor ID: ");
        // Validate if the input is a positive integer
        if (scanf("%d", &new_doctor->doctorID) != 1 || new_doctor->doctorID <= 0) {
            printf("Invalid ID. Please enter a positive integer.\n");
            while (getchar() != '\n'); // Clear input buffer
        }
    } while (new_doctor->doctorID <= 0);

    // Check if doctor ID already exists
    Doctor *current = doctorList;
    while (current != NULL) {
        if (current->doctorID == new_doctor->doctorID) {
            printf("Doctor ID already exists. Please enter a different ID.\n");
            free(new_doctor);
            return;
        }
        current = current->next;
    }

    // Clear input buffer
    while (getchar() != '\n');

    // Input for doctor full name
    printf("Enter doctor full name:Dr.");
    fgets(new_doctor->fullNameDoc, sizeof(new_doctor->fullNameDoc), stdin);
    strtok(new_doctor->fullNameDoc, "\n"); // Remove newline character

    // Input for doctor specialty
    printf("Select doctor specialty:\n");
    printf("0: General Medicine\n");
    printf("1: Pediatrics\n");
    printf("2: Cardiology\n");
    printf("3: Oncology\n");
    printf("4: Neurology\n");
    printf("5: Orthopedics\n");
    printf("6: Surgery\n");
    printf("7: OTHER_SPECIALTY\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);

    // Read and validate specialty choice
    if (choice < GENERAL_MEDICINE || choice > OTHER_SPECIALTY) {
        printf("Invalid choice. Setting specialty to Other.\n");
        new_doctor->specialty = OTHER_SPECIALTY;
        new_doctor->OtherSpecialty[0] = '\0';
    } else if (choice == OTHER_SPECIALTY) {
        // Handle other specialty input
        printf("Enter the specialty: ");
        while (getchar() != '\n'); // Clear input buffer
        fgets(new_doctor->OtherSpecialty, sizeof(new_doctor->OtherSpecialty), stdin);
        strtok(new_doctor->OtherSpecialty, "\n"); // Remove newline character
        new_doctor->specialty = OTHER_SPECIALTY;
    } else {
        new_doctor->specialty = (Specialty)choice;
        new_doctor->OtherSpecialty[0] = '\0'; // Clear custom specialty
    }

    // Initialize diagnostic list for the new doctor
    new_doctor->diagnosticList = NULL;

    // Insert new doctor at the beginning of the linked list
    new_doctor->next = doctorList;
    doctorList = new_doctor;

    printf("Doctor record added successfully.\n");
}

// Function to update an existing doctor in the patientList
void update_doctor() {
    int doctorID;

    // Input validation for doctor ID (positive value)
    do {
        printf("Enter doctor ID to update: ");
        // Validate if the input is a positive integer
        if (scanf("%d", &doctorID) != 1 || doctorID <= 0) {
            printf("Invalid ID. Please enter a positive integer.\n");
            while (getchar() != '\n'); // Clear input buffer
        }
    } while (doctorID <= 0);

    // Search for the doctor by ID
    Doctor *current = doctorList;
    Doctor *to_update = NULL;

    while (current != NULL) {
        if (current->doctorID == doctorID) {
            to_update = current;
            break;
        }
        current = current->next;
    }

    // If doctor not found, return
    if (to_update == NULL) {
        printf("Doctor not found.\n");
        return;
    }

   // Input for doctor full name
printf("Enter updated full name:Dr.");
            getchar(); // Clear the newline character from the buffer
            fgets(to_update->fullNameDoc, sizeof(to_update->fullNameDoc), stdin);
            strtok(to_update->fullNameDoc, "\n"); // Remove trailing newline character

    // Input for doctor specialty
    printf("Select updated doctor specialty:\n");
    printf("0: General Medicine\n");
    printf("1: Pediatrics\n");
    printf("2: Cardiology\n");
    printf("3: Oncology\n");
    printf("4: Neurology\n");
    printf("5: Orthopedics\n");
    printf("6: Surgery\n");
    printf("7: OTHER_SPECIALTY\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);
    if  (choice == 7) {
        printf("Enter specialty: ");
        while (getchar() != '\n'); // Clear input buffer
        fgets(to_update->OtherSpecialty, sizeof(to_update->OtherSpecialty), stdin);
        strtok(to_update->OtherSpecialty, "\n"); // Remove newline character
        to_update->specialty = OTHER_SPECIALTY;
    } else if (choice < GENERAL_MEDICINE || choice > SURGERY) {
        printf("Invalid choice. Setting specialty to Other.\n");
        to_update->specialty = OTHER_SPECIALTY;
        to_update->OtherSpecialty[0] = '\0';
    } else {
        to_update->specialty = (Specialty)choice;
        to_update->OtherSpecialty[0] = '\0'; // Clear custom specialty
    }

    printf("Doctor record updated successfully.\n");
}

// Function to delete a doctor from the patientList
void delete_doctor() {
    int doctorID;

    // Input validation for doctor ID (positive value)
    do {
        printf("Enter doctor ID to delete: ");
        // Validate if the input is a positive integer
        if (scanf("%d", &doctorID) != 1 || doctorID <= 0) {
            printf("Invalid ID. Please enter a positive integer.\n");
            while (getchar() != '\n'); // Clear input buffer
        }
    } while (doctorID <= 0);

    // Search for the doctor by ID
    Doctor *current = doctorList;
    Doctor *prev = NULL; // Pointer to the previous node

    while (current != NULL) {
        if (current->doctorID == doctorID) {
            // Handle deletion based on node position
            if (prev == NULL) { // Deleting the head node
                doctorList = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Doctor deleted successfully.\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Doctor not found.\n");
}

// Function to search for a doctor
void search_doctor() {
    int choice;

    // Display search options
    printf("Search for a doctor by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("3. Specialty\n");
    printf("Enter your choice: ");

    // Input validation for choice
    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
        printf("Invalid choice. Please enter a number between 1 and 3: ");
        while (getchar() != '\n'); // Clear input buffer
    }

    switch (choice) {
        case 1: {
            // Input validation and search by doctor ID
            int id;
            do {
                printf("Enter doctor ID to search: ");
                scanf("%d", &id);
                if (id <= 0) {
                    printf("Invalid ID. Please enter a positive integer: ");
                    while (getchar() != '\n'); // Clear input buffer
                }
            } while (id <= 0);

            Doctor *found = NULL;
            Doctor *current = doctorList;
            while (current != NULL) {
                if (current->doctorID == id) {
                    found = current;
                    break;
                }
                current = current->next;
            }
            if (found != NULL) {
                printf("Doctor found by ID %d:\n", id);
                printf("Name:Dr.%s\n", found->fullNameDoc);
                printf("Specialty: ");
                if (found->specialty == OTHER_SPECIALTY) {
                    printf("%s\n", found->OtherSpecialty);
                } else {
                    printf("%d\n", found->specialty);
                }
                // Print additional information if needed
                // For example, you can print doctor's age, gender, etc. here
            } else {
                printf("Doctor with ID %d not found.\n", id);
            }
            break;
        }
        case 2: {
            // Search by doctor name
            char name[50];
            printf("Enter doctor name to search:Dr.");
            getchar(); // Consume the newline character left in the buffer
            fgets(name, sizeof(name), stdin);
            strtok(name, "\n"); // Remove newline character
            Doctor *found = NULL;
            Doctor *current = doctorList;
            while (current != NULL) {
                if (strcmp(current->fullNameDoc, name) == 0) {
                    found = current;
                    break;
                }
                current = current->next;
            }
            if (found != NULL) {
                printf("Doctor found by name Dr.'%s':\n", name);
                printf("ID: %d\n", found->doctorID);
                printf("Specialty: ");
                if (found->specialty == OTHER_SPECIALTY) {
                    printf("%s\n", found->OtherSpecialty);
                } else {
                    printf("%d\n", found->specialty);
                }
                // Print additional information if needed
            } else {
                printf("Doctor with name Dr.'%s' not found.\n", name);
            }
            break;
        }
        case 3: {
            // Search by doctor specialty
            int specialty;
            printf("Enter doctor specialty to search:\n");
            printf("0: General Medicine\n");
            printf("1: Pediatrics\n");
            printf("2: Cardiology\n");
            printf("3: Oncology\n");
            printf("4: Neurology\n");
            printf("5: Orthopedics\n");
            printf("6: Surgery\n");
            printf("7: Other\n");
            while (scanf("%d", &specialty) != 1 || specialty < 0 || specialty > 7) {
                printf("Invalid choice. Please enter a number between 0 and 7: ");
                while (getchar() != '\n'); // Clear input buffer
            }
            if (specialty == 7) {
                char otherSpecialty[50]; // Declare otherSpecialty variable
                printf("Enter other specialty: ");
                getchar(); // Consume the newline character left in the buffer
                fgets(otherSpecialty, sizeof(otherSpecialty), stdin);
                strtok(otherSpecialty, "\n"); // Remove newline character
                Doctor *current = doctorList;
                int found = 0;
                while (current != NULL) {
                    if (current->specialty == OTHER_SPECIALTY && strcmp(current->OtherSpecialty, otherSpecialty) == 0) {
                        printf("Doctor found with Other specialty '%s':\n", otherSpecialty);
                        printf("Name:Dr.%s\n", current->fullNameDoc);
                        printf("ID: %d\n", current->doctorID);
                        printf("Specialty: %s\n", current->OtherSpecialty);
                        found = 1;
                    }
                    current = current->next;
                }
                if (!found) {
                    printf("No doctors found with the specified specialty.\n");
                }
            } else {
                Doctor *current = doctorList;
                int found = 0;
                while (current != NULL) {
                    if (current->specialty == specialty) {
                        printf("Doctor found with specialty '%d':\n", specialty);
                        printf("Name:Dr.%s\n", current->fullNameDoc);
                        printf("ID: %d\n", current->doctorID);
                        printf("Specialty: ");
                        if (current->specialty == OTHER_SPECIALTY) {
                            printf("%s\n", current->OtherSpecialty);
                        } else {
                            printf("%d\n", current->specialty);
                        }
                        found = 1;
                    }
                    current = current->next;
                }
                if (!found) {
                    printf("No doctors found with the specified specialty.\n");
                }
            }
            break;
        }
        default:
            printf("Invalid choice.\n");
    }
}



// Function to list diagnostic records by doctor ID
void list_diagnostics_by_doctorID() {
    int doctorID;

    // Input validation for doctor ID (positive value)
    do {
        printf("Enter doctor ID to list diagnostics: ");
        scanf("%d", &doctorID);

        if (doctorID <= 0) {
            printf("Invalid ID. Please enter a positive integer.\n");
        }
    } while (doctorID <= 0);

    // Check if diagnostic records exist
    if (diagnosticList == NULL) {
        printf("No diagnostic records found.\n");
        return;
    }

    // Traverse the diagnostic records linked list to find records for the specified doctor ID
    Diagnostic *current = diagnosticList;
    int found = 0;
    while (current != NULL) {
        if (current->doctorID == doctorID) {
            found = 1;
            printf("Diagnostic record found for Doctor ID %d:\n", doctorID);
            printf("Patient ID: %d\n", current->patientID);
            printf("Diagnosis: ");
            // Print diagnosis type based on enum value
            switch (current->diagnosis) {
                case Hypertension:
                    printf("Hypertension\n");
                    break;
                case Type_1Diabetes:
                    printf("Type 1 Diabetes\n");
                    break;
                case Type_2Diabetes:
                    printf("Type 2 Diabetes\n");
                    break;
                case Traffic_Accidents_Injuries:
                    printf("Traffic Accidents Injuries\n");
                    break;
                case Acute_Chronic_Infections:
                    printf("Acute or Chronic Infections\n");
                    break;
                case Cardiovascular_Diseases:
                    printf("Cardiovascular Diseases\n");
                    break;
                case Cancerous_Tumors:
                    printf("Cancerous Tumors\n");
                    break;
                case Respiratory_Conditions:
                    printf("Respiratory Conditions\n");
                    break;
                case OTHER_DIAGNOSTIC:
                    printf("Other Diagnostic: %s\n", current->OtherDiagnosis);
                    break;
                default:
                    printf("Unknown Diagnosis\n");
                    break;
            }
            // Print diagnosis date and next appointment date
            printf("Diagnosis Date: %d-%d-%d\n", current->diagDate.day, current->diagDate.month, current->diagDate.year);
            printf("Next Appointment: %d-%d-%d\n", current->nextAppointment.day, current->nextAppointment.month, current->nextAppointment.year);
            printf("-------------------------\n");
        }
        current = current->next; // Move to the next diagnostic record
    }

    // Print message if no diagnostic records found for the specified doctor ID
    if (!found) {
        printf("No diagnostic records found for Doctor ID %d.\n", doctorID);
    }
}

// Function to deallocate memory allocated for the doctor linked list
void free_doctor_memory() {
    Doctor *current = doctorList;
    while (current != NULL) {
        Doctor *temp = current;
        current = current->next;

        // Free diagnostic records for this doctor
        Diagnostic *diagnostic = temp->diagnosticList;
        while (diagnostic != NULL) {
            Diagnostic *temp_diag = diagnostic;
            diagnostic = diagnostic->next;
            free(temp_diag);
        }

        free(temp); // Freeing memory for the current doctor node
    }
    doctorList = NULL; // Resetting the head pointer to NULL after freeing all memory
}

int main() {
    int choice;

    while (1) {
        printf("\nPatient Diagnostic System\n");
        printf("-------------------------\n");
        printf("1: Patient management\n");
        printf("2: Diagnostic management\n");
        printf("3: Doctor management\n");
        printf("0: Exit\n");
        printf("-------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                {
                    int patient_choice;
                    while (1) {
                        printf("\nPatient Management System\n");
                        printf("-------------------------\n");
                        printf("1: Add patient\n");
                        printf("2: Update patient\n");
                        printf("3: Delete patient\n");
                        printf("4: Search patient\n");
                        printf("5: Print patient\n");
                        printf("0: Back to main menu\n");
                        printf("-------------------------\n");
                        printf("Enter your choice: ");
                        scanf("%d", &patient_choice);

                        switch (patient_choice) {
                            case 1:
                                add_patient();
                                break;
                            case 2:
                                update_patient();
                                break;
                            case 3:
                                delete_patient();
                                break;
                            case 4:
                                search_patient();
                                break;
                            case 5:
                                print_patient();
                                break;
                            case 0:
                                break;
                            default:
                                printf("Invalid choice. Please enter a number between 0 and 5.\n");
                        }

                        if (patient_choice == 0)
                            break;
                    }
                    break;
                }
            case 2:
                {
                    int diagnostic_choice;
                    while (1) {
                        printf("\nDiagnostic Management System\n");
                        printf("----------------------------\n");
                        printf("1: Add diagnostic\n");
                        printf("2: Update diagnostic\n");
                        printf("3: Delete diagnostic\n");
                        printf("4: Search diagnostic\n");
                        printf("5: Print diagnostic\n");
                        printf("0: Back to main menu\n");
                       printf("----------------------------\n");
                        printf("Enter your choice: ");
                        scanf("%d", &diagnostic_choice);

                        switch (diagnostic_choice) {
                            case 1:
                                add_diagnostic();
                                break;
                            case 2:
                                update_diagnostic();
                                break;
                            case 3:
                                delete_diagnostic();
                                break;
                            case 4:
                                search_diagnostic();
                                break;
                            case 5:
                                print_diagnostic();
                                break;
                            case 0:
                                break;
                            default:
                                printf("Invalid choice. Please enter a number between 0 and 5.\n");
                        }

                        if (diagnostic_choice == 0)
                            break;
                    }
                    break;
                }
            case 3:
                {
                    int doctor_choice;
                    while (1) {
                        printf("\nDoctor Management System\n");
                        printf("------------------------\n");
                        printf("1: Add Doctor\n");
                        printf("2: Update Doctor\n");
                        printf("3: Delete Doctor\n");
                        printf("4: Search Doctor\n");
                        printf("5: Print List Diagnostics of Doctor \n");
                        printf("0: Back to main menu\n");
                        printf("------------------------\n");
                        printf("Enter your choice: ");
                        scanf("%d", &doctor_choice);

                        switch (doctor_choice) {
                            case 1:
                                add_doctor();
                                break;
                            case 2:
                                update_doctor();
                                break;
                            case 3:
                                delete_doctor();
                                break;
                            case 4:
                                search_doctor();
                                break;
                            case 5:
                                list_diagnostics_by_doctorID();
                                break;
                            case 0:
                                break;
                            default:
                                printf("Invalid choice. Please enter a number between 0 and 5.\n");
                        }

                        if (doctor_choice == 0)
                            break;
                    }
                    break;
                }
            case 0:
                // Free memory and exit the program
                free_patient_memory();
                free_diagnostic_memory();
                free_doctor_memory();

                printf("Exiting the program...\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a number between 0 and 3.\n");
        }
    }
    return 0;
}
