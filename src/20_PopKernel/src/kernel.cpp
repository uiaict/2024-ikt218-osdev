// The memory related functions in this file are based on Per-Arne Andersen's implementation found at https://perara.notion.site/IKT218-Advanced-Operating-Systems-2024-bfa639380abd46389b5d69dcffda597a

extern "C" {
    #include "libc/stdio.h"
    #include "libc/string.h"
    #include "memory.h"
    #include "pit.h"
    #include "io.h"
    #include "macros.h"
    #include "keyboard.h"
    
    
    int kernel_main(void);
}

#include "applications/demos.h"
#include "applications/song.h"

// Existing global operator new overloads
void* operator new(size_t size) {
    return malloc(size);
}

void* operator new[](size_t size) {
    return malloc(size);
}

// Existing global operator delete overloads
void operator delete(void* ptr) noexcept {
    free(ptr);
}

void operator delete[](void* ptr) noexcept {
    free(ptr);
}

// Add sized-deallocation functions
void operator delete(void* ptr, size_t size) noexcept {
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}

void operator delete[](void* ptr, size_t size) noexcept {
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}

int kernel_main(){
    // Loading screen. Not needed at all, but looks cool
    disableCursor();
    printf("Starting OS [");
    videoMemory[cursorPos + 60] = ']';
    
    for (int i = 0; i < 30; i++){
        putchar('|');
        sleepInterrupt(100);
    }

    cursorVertical;  
    clearScreen();

    charBuffer[0];
    bufferIndex = 0;
    
    // Prints the UiA OS logo. The group name is really PopKernel, but there isnt enough space for the whole name. So UiA OS it is.
    printf("    ooooo    ooooo  o8o         .o.              .oooooo.     .oooooooo  \n"); 
    printf("     888      888   ***        .888.            d8P    Y8b   d88P     Y8 \n"); 
    printf("     888      888  ooooo      .88888.          888      888  Y88bo.      \n"); 
    printf("     888      888   888      .88   88.         888      888    Y8888o.   \n"); 
    printf("     888      888   888     .88ooooo88.        888      888       `Y88b  \n"); 
    printf("       88    88     888    .888     888.        88b    d88  oo      .d8P \n"); 
    printf("         8888      o888o  o8888o   o8888o        Y8bood8P    Y88888888P  \n"); 
    

    // Prints the group members
    printf("\n              Created by Tobias Kallevik, Kevin Nguyen and Jone Viste\n");

    printf("\nType 'help' for a list of commands to run demos or press 'esc' to enter drawing mode.\n");
    printf("Be aware that some of the demos are destructive and require a reboot\n");



    // Demo loop
    while (true){
        char input[100];
        scanf("%s", input);

        // Prints the help menu
        if (strcmp(input, "help") == 0){ 
            printf("Available commands:\n");
            printf("'print' - Runs printf demo\n");
            printf("'memory' - Runs memory demo\n");
            printf("'pagefault' - Runs page fault demo\n");
            printf("'pit' - Runs pit demo\n");
            printf("'isr' - Runs isr demo\n");
            printf("'song' - Runs song demo\n");
            printf("'color' - Color change demo\n");
            printf("'cursor' - Cursor change demo\n");
            printf("'exit' - Exits demo mode and allows for free typing\n");
        }

        // Runs printf demo
        else if (strcmp(input, "print") == 0){
            printDemo();
        }

        // Runs memory demo
        else if (strcmp(input, "memory") == 0){
            void* someMemory = malloc(12345); 
            void* memory2 = malloc(54321); 
            void* memory3 = malloc(13331);
            char* memory4 = new char[1000](); 
        }

        // Runs page fault demo
        else if (strcmp(input, "pagefault") == 0){
            pageFaultDemo();
        }

        // Runs pit demo
        else if (strcmp(input, "pit") == 0){
            pitDemo();
        }

        else if (strcmp(input, "isr") == 0){
            isrDemo();
        }

        // Runs song demo. Implementation direcly in main. Implementing in demos.cpp caused issues.
        else if (strcmp(input, "song") == 0){
            printf("Available songs:\n");
            printf("0. Play All\n");
            printf("1. Music1\n");
            printf("2. Music2\n");
            printf("3. Music3\n");
            printf("4. Music4\n");
            printf("5. Music5\n");
            printf("6. Music6\n");
            printf("7. Star Wars\n");
            printf("8. Battlefield 1942\n");

            printf("Enter the number of the song you want to play: ");
            int choice;
            scanf("%d", &choice);

            if (choice < 0 || choice > 8){
                printf("Invalid song number. Exiting demo.\n");
                continue;
            }
            
            Song* songs[] = {
                new Song{music1, sizeof(music1) / sizeof(Note)},
                new Song{music2, sizeof(music2) / sizeof(Note)},
                new Song{music3, sizeof(music3) / sizeof(Note)},
                new Song{music4, sizeof(music4) / sizeof(Note)},
                new Song{music5, sizeof(music5) / sizeof(Note)},
                new Song{music6, sizeof(music6) / sizeof(Note)},
                new Song{starwarsTheme, sizeof(starwarsTheme) / sizeof(Note)},
                new Song{battlefield1942Theme, sizeof(battlefield1942Theme) / sizeof(Note)},
            };

            uint32_t nSongs = sizeof(songs) / sizeof(Song*); // Get the number of songs

            SongPlayer* player = createSongPlayer(); // Create a new SongPlayer instance
            
            // Play the songs
            if (choice == 0) {
                for(uint32_t i = 0; i < nSongs; i++){
                    printf("Playing Song...\n");
                    player->playSong(songs[i]);
                    printf("Finished playing the song.\n");
                }
            } 
    
            else {
                printf("Playing Song...\n");
                player->playSong(songs[choice - 1]);
                printf("Finished playing the song.\n");
            }
        }


        // Runs color change demo
        else if (strcmp(input, "color") == 0){
            changeColorDemo();
        }

        // Runs cursor change demo
        else if (strcmp(input, "cursor") == 0){
            changeCursorDemo();
        }
        // Exits demo mode
        else if (strcmp(input, "exit") == 0){
            printf("Exiting demo mode. You can still enter drawing mode by pressing 'esc'\n");
            break;
        }

        else {
            printf("Unknown command. Type 'help' for a list of commands.\n");
        }
    }

    while(true);
}