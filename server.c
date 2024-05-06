#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080
#define MAX_LINE_LENGTH 1024

char* status(const char *searchString) {
    FILE *file = fopen("../myanimelist.csv", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return NULL;
    }

    size_t resultSize = 1024;
    char *result = (char *)malloc(resultSize * sizeof(char));
    if (result == NULL) {
        printf("Memory allocation error!\n");
        fclose(file);
        return NULL;
    }
    result[0] = '\0';

    int count = 1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        char *token = strtok(line, ",");
        int column = 1;
        char thirdColumn[MAX_LINE_LENGTH];
        while (token != NULL) {
            if (column == 3) {
                if (strstr(token, searchString) != NULL) {
                    token = strtok(NULL, ",");
                    snprintf(result + strlen(result), resultSize - strlen(result), "%s\n", token);
                    break;
                }
            }
            token = strtok(NULL, ",");
            column++;
        }
    }

    fclose(file);
    return result;
}

char* tampil() {
    FILE *file = fopen("../myanimelist.csv", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return NULL;
    }

    size_t resultSize = 1024;
    char *result = (char *)malloc(resultSize * sizeof(char));
    if (result == NULL) {
        printf("Memory allocation error!\n");
        fclose(file);
        return NULL;
    }
    result[0] = '\0';

    int count = 1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        char *token = strtok(line, ",");
        int column = 1;
        char thirdColumn[MAX_LINE_LENGTH];
        while (token != NULL) {
            if (column == 3) {
                strcpy(thirdColumn, token);
            }
            if (column == 4) {
                snprintf(result + strlen(result), resultSize - strlen(result), "%d. %s\n", count, thirdColumn);
                count++;
                break;
            }
            token = strtok(NULL, ",");
            column++;
        }
    }

    fclose(file);
    return result;
}

char* genre(const char *searchString) {
    FILE *file = fopen("../myanimelist.csv", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return NULL;
    }

    size_t resultSize = 1024;
    char *result = (char *)malloc(resultSize * sizeof(char));
    if (result == NULL) {
        printf("Memory allocation error!\n");
        fclose(file);
        return NULL;
    }
    result[0] = '\0';

    int count = 1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        char *token = strtok(line, ",");
        int column = 1;
        char thirdColumn[MAX_LINE_LENGTH];
        while (token != NULL) {
            if (column == 3) {
                strcpy(thirdColumn, token);
            }
            if (column == 2) {
                if (strstr(token, searchString) != NULL) {
                    token = strtok(NULL, ",");
                    snprintf(result + strlen(result), resultSize - strlen(result), "%d. %s\n", count, token);
                    count++;
                    break;
                }
            }
            token = strtok(NULL, ",");
            column++;
        }
    }

    fclose(file);
    return result;
}

char* hari(const char *searchString) {
    FILE *file = fopen("../myanimelist.csv", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return NULL;
    }

    size_t resultSize = 1024;
    char *result = (char *)malloc(resultSize * sizeof(char));
    if (result == NULL) {
        printf("Memory allocation error!\n");
        fclose(file);
        return NULL;
    }
    result[0] = '\0';

    int count = 1;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        char *token = strtok(line, ",");
        int column = 1;
        char thirdColumn[MAX_LINE_LENGTH];
        while (token != NULL) {
            if (column == 3) {
                strcpy(thirdColumn, token);
            }
            if (column == 1) {
                if (strstr(token, searchString) != NULL) {
                    for(int i = 0; i<2; i++){
                        token = strtok(NULL, ",");
                    }
                    snprintf(result + strlen(result), resultSize - strlen(result), "%d. %s\n", count, token);
                    count++;
                    break;
                }
            }
            token = strtok(NULL, ",");
            column++;
        }
    }

    fclose(file);
    return result;
}

int findrow(const char *searchString) {
    FILE *file = fopen("../myanimelist.csv", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return -1; // Return -1 to indicate an error
    }

    int row = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        row++; // Increment row number for each line read
        line[strcspn(line, "\n")] = '\0';
        char *token = strtok(line, ",");
        int column = 1;
        while (token != NULL) {
            if (column == 3) {
                if (strstr(token, searchString) != NULL) {
                    fclose(file);
                    return row; // Return the row number if search string found
                }
            }
            token = strtok(NULL, ",");
            column++;
        }
    }

    fclose(file);
    return 0; // Return 0 if search string is not found
}

void deleteRow(const char *filename, int rowToDelete) {
    FILE *fp, *tempFile;
    char buffer[1024];
    int row = 0;

    // Open the original CSV file for reading
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Open a temporary file for writing
    tempFile = fopen("temp.csv", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file!\n");
        fclose(fp);
        return;
    }

    // Read each line from the original file and write to temporary file, skipping the specified row
    while (fgets(buffer, sizeof(buffer), fp)) {
        row++;

        // Skip the row to be deleted
        if (row == rowToDelete)
            continue;

        fputs(buffer, tempFile);
    }

    // Close both files
    fclose(fp);
    fclose(tempFile);

    // Remove the original file
    remove(filename);

    // Rename the temporary file to the original filename
    rename("temp.csv", filename);
}

void addRow(const char *filename, const char *rowData) {
    FILE *file = fopen(filename, "a"); // Open the file in append mode
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "%s\n", rowData); // Write the data to the file
    fclose(file); // Close the file
}


#define MAX_COLS 100
#define MAX_ROW_LEN 1000

void editRow(const char *filename, int rowNumber, const char *rowData) {
    FILE *file = fopen(filename, "r"); // Open the file in read mode
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char rows[MAX_COLS][MAX_ROW_LEN];
    int currentRow = 0;

    // Read each line of the CSV file
    while (fgets(rows[currentRow], MAX_ROW_LEN, file) != NULL && currentRow < MAX_COLS) {
        if (currentRow == rowNumber - 1) {
            // If this is the row we want to modify, replace it with the new data
            strncpy(rows[currentRow], rowData, MAX_ROW_LEN - 1);
            rows[currentRow][MAX_ROW_LEN - 1] = '\0'; // Ensure null-termination
            break;
        }
        currentRow++;
    }
    fclose(file);

    // Reopen the file in write mode to overwrite the existing content
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Write the modified rows back to the file
    for (int i = 0; i <= currentRow; i++) {
        fprintf(file, "%s", rows[i]);
    }
    fclose(file);
}

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT , &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    while(1){
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        valread = read( new_socket , buffer, 1024);

        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';

        char *firstWord = strtok(buffer, " ");
        char *restOfString = strtok(NULL, "");

        if(strcmp("status", firstWord) == 0){
            char* statres = status(restOfString);
            send(new_socket, statres, strlen(statres), 0);
            memset(statres, 0, strlen(statres)); // Clear memory
        }else if(strcmp("tampilkan", firstWord) == 0){
            char* tampres = tampil();
            send(new_socket, tampres, strlen(tampres), 0);
            memset(tampres, 0, strlen(tampres)); // Clear memory
        }else if(strcmp("genre", firstWord) == 0){
            char* genreres = genre(restOfString);
            send(new_socket, genreres, strlen(genreres), 0);
            memset(genreres, 0, strlen(genreres)); // Clear memory
        }else if(strcmp("hari", firstWord) == 0){
            char* harires = hari(restOfString);
            send(new_socket, harires, strlen(harires), 0);
            memset(harires, 0, strlen(harires)); // Clear memory
        }else if(strcmp("delete", firstWord) == 0){
            int delrow = findrow(restOfString);
            deleteRow("../myanimelist.csv", delrow);
            char delmessage[100] = "anime berhasil dihapus";
            send(new_socket, delmessage, strlen(delmessage), 0);
        }else if(strcmp("add", firstWord) == 0){
            addRow("../myanimelist.csv", restOfString);
            char addmessage[100] = "anime berhasil ditambahkan";
        }else if(strcmp("edit",  firstWord)){
            char *restOfStringCopy = strdup(restOfString); 
            char *secondWord = strtok(restOfStringCopy, ","); 
            char *anotherword = strtok(NULL, "");
            int editrow = findrow(secondWord);
            if (editrow != 0) { // If the anime to be edited is found
                editRow("../myanimelist.csv", editrow, anotherword);
                char editmessage[100] = "Anime berhasil diubah";
                send(new_socket, editmessage, strlen(editmessage), 0);
            } else {
                char notfoundmsg[100] = "Anime tidak ditemukan";
                send(new_socket, notfoundmsg, strlen(notfoundmsg), 0);
            }
            memset(restOfStringCopy, 0, strlen(restOfStringCopy)); // Clear memory
        }else{
            char invalidmsg[100] = "Invalid Command";
            send(new_socket, invalidmsg, strlen(invalidmsg), 0);
        }
    }
}
