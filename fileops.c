#include "abk.h"

// check duplicate contact
int contact_exists(const char *name) {
    Contact c;
    FILE *fp = fopen("telephone.csv", "r");
    if (!fp) return 0;

    while (fscanf(fp, "%49[^,],%19[^,],%49[^\n]\n",
                  c.name, c.phone, c.email) != EOF) {
        if (strcmp(c.name, name) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

// ADD CONTACT
void add_contact() {
    Contact c;
    char choice;

    printf("Enter Name: ");
    scanf(" %[^\n]", c.name);

    if (strlen(c.name) == 0) {
        printf("Name is mandatory!\n");
        return;
    }

    if (contact_exists(c.name)) {
        printf("Contact already exists. Overwrite? (y/n): ");
        scanf(" %c", &choice);
        if (choice != 'y') return;
        delete_contact(); // remove old
    }

    printf("Enter Phone: ");
    scanf("%s", c.phone);
    printf("Enter Email: ");
    scanf("%s", c.email);

    printf("Save contact? (y/n): ");
    scanf(" %c", &choice);
    if (choice != 'y') {
        printf("Contact not saved.\n");
        return;
    }

    FILE *fp = fopen("telephone.csv", "a");
    fprintf(fp, "%s,%s,%s\n", c.name, c.phone, c.email);
    fclose(fp);

    log_event("Contact Added");
    printf("Contact saved successfully.\n");
}

// VIEW CONTACTS
void view_contacts() {
    Contact c;
    FILE *fp = fopen("telephone.csv", "r");
    if (!fp) {
        printf("No contacts found.\n");
        return;
    }

    printf("\n--- CONTACT LIST ---\n");
    while (fscanf(fp, "%49[^,],%19[^,],%49[^\n]\n",
                  c.name, c.phone, c.email) != EOF) {
        printf("Name: %s | Phone: %s | Email: %s\n",
               c.name, c.phone, c.email);
    }
    fclose(fp);
}

// SEARCH CONTACT
void search_contact() {
    char key[50];
    Contact c;
    int found = 0;

    printf("Enter name to search: ");
    scanf(" %[^\n]", key);

    FILE *fp = fopen("telephone.csv", "r");
    if (!fp) {
        printf("File not found.\n");
        return;
    }

    while (fscanf(fp, "%49[^,],%19[^,],%49[^\n]\n",
                  c.name, c.phone, c.email) != EOF) {
        if (strcmp(c.name, key) == 0) {
            printf("Found → %s | %s | %s\n",
                   c.name, c.phone, c.email);
            found = 1;
        }
    }
    fclose(fp);

    if (!found)
        printf("Contact not found.\n");
}

// EDIT CONTACT
void edit_contact() {
    char name[50], choice;
    Contact c;
    int found = 0;

    printf("Enter name to edit: ");
    scanf(" %[^\n]", name);

    FILE *fp = fopen("telephone.csv", "r");
    FILE *temp = fopen("temp.csv", "w");

    while (fscanf(fp, "%49[^,],%19[^,],%49[^\n]\n",
                  c.name, c.phone, c.email) != EOF) {
        if (strcmp(c.name, name) == 0) {
            found = 1;
            printf("Update this contact? (y/n): ");
            scanf(" %c", &choice);
            if (choice == 'y') {
                printf("New Phone: ");
                scanf("%s", c.phone);
                printf("New Email: ");
                scanf("%s", c.email);
                log_event("Contact Edited");
            }
        }
        fprintf(temp, "%s,%s,%s\n", c.name, c.phone, c.email);
    }

    fclose(fp);
    fclose(temp);
    remove("telephone.csv");
    rename("temp.csv", "telephone.csv");

    if (!found)
        printf("Contact not found.\n");
    else
        printf("Contact updated.\n");
}

// DELETE CONTACT
void delete_contact() {
    char name[50], choice;
    Contact c;
    int found = 0;

    printf("Enter name to delete: ");
    scanf(" %[^\n]", name);

    FILE *fp = fopen("telephone.csv", "r");
    FILE *temp = fopen("temp.csv", "w");

    while (fscanf(fp, "%49[^,],%19[^,],%49[^\n]\n",
                  c.name, c.phone, c.email) != EOF) {
        if (strcmp(c.name, name) == 0) {
            found = 1;
            printf("Confirm delete? (y/n): ");
            scanf(" %c", &choice);
            if (choice == 'y') {
                log_event("Contact Deleted");
                continue;
            }
        }
        fprintf(temp, "%s,%s,%s\n", c.name, c.phone, c.email);
    }

    fclose(fp);
    fclose(temp);
    remove("telephone.csv");
    rename("temp.csv", "telephone.csv");

    if (!found)
        printf("Contact not found.\n");
    else
        printf("Delete operation completed.\n");
}


