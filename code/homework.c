#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

/*
 *The max character user can input in windows command line is 4096 
*/
char input_zone[4096];

/*declear zone*/
int process_input(char userInput[]);
int show_DIR_list(char cmd[]);
void showCurrentDIR();
void changeWorkDIR(char cmd[]);
void NewDir(char cmd[]);
void RemoveDIR(char cmd[]);
void Rename(char cmd[]);
void Copy(char cmd[]);
void CopyFile(char source[],char destination[]);
void CopyFold(char source[],char destination[]);
void Find(char cmd[]);
void do_find(char dirName[],char file_or_fold_name[]);
/*declear zone*/


void main(){
    printf("Simple terminal made by myself version alpha 0.1\n");

    while (1)
    {
        memset(input_zone,'\0',sizeof(input_zone));
        printf("Please input your command: "); 
        gets(input_zone);
        /*if user did not input anything*/
        if(input_zone[0] == '\0'){
            continue;
        }
        process_input(input_zone);
    }
            
}


/*process user input*/
int process_input(char userInput[]){
    
    int i=0,j=0;//index
    char operation[255];
    memset(operation,'\0',sizeof(operation));

    /*clear out ' ' before command if ' ' existed*/
    while (userInput[i] == ' ')
    {
        /* Doing nothing */
        i++;
    }
    

    /*check command,scanning the character until ' ' or '\0'*/
    while(userInput[i]!='\0'){
        operation[j] = userInput[i];
        i++;
        j++;
        if(userInput[i] == ' '){
            break;
        }
    }

    /*Checking operation*/
    if(strcmp(operation,"pwd")==0){
        /*Execute command: pwd*/
        showCurrentDIR();

    }else if(strcmp(operation,"exit")==0){

        printf("Program has closed\n");
        /* Execute command : exit */
        _exit(0);

    }else if(strcmp(operation,"list")==0){

        /*Read directory*/
        show_DIR_list(userInput);

    }else if(strcmp(operation,"cd") == 0){

        /*change work directory*/
        changeWorkDIR(userInput);

    }else if(strcmp(operation,"mkdir") == 0){
        /*new directory*/
        NewDir(userInput);

    }else if(strcmp(operation,"rmdir") == 0){
        /*remove directory*/
        RemoveDIR(userInput);

    }else if(strcmp(operation,"rename") == 0){
        /*rename*/
        Rename(userInput);

    }else if(strcmp(operation,"copy") == 0){
        /*copy file or directory*/
        Copy(userInput);

    }else if(strcmp(operation,"find") ==0 ){
        /*find and search file or fold*/
        Find(userInput);

    }else{
        printf("\"%s\" is not a valid command\n\n",operation);
    }
    
    
    return 0;/*exit function*/
}


/*command:pwd*/
void showCurrentDIR(){
    char c_DIR[256];
    /*get current directory*/
        getcwd(c_DIR,sizeof(c_DIR));
        /*show current directory*/
        printf("%s\n\n",c_DIR);
}


/*command :list*/
int show_DIR_list(char cmd[]){
    int i = 0,j = 0;//index
    DIR *dir_list;
    /*get directory from the command*/
    char target_dir[256];
    /*get current directory*/
    char current_dir[256];
    /*to get files info*/
    struct dirent *filesINFO;
    
    memset(target_dir,'\0',sizeof(target_dir));
    memset(current_dir,'\0',sizeof(current_dir));

    while (cmd[i]!='\0')
    {
        i++;

        /*if first character is space,jump through it until it isn't space*/
        if(cmd[0] == ' '){
            while(cmd[i]== ' '){
                i++;
                /*in case of out of index*/
                if(cmd[i] == '\0'){
                    break;
                }
            }
        }

        /*jump through operation*/
        while(cmd[i]!= ' '){
            i++;
            /*in case of out of index*/
            if(cmd[i] == '\0'){
                break;
            }
        }

        /*if chracter space appeared second times , record the target directory*/
        if(i!=0 && cmd[i] == ' '){
            /*jump though space*/
            while(cmd[i]==' '){
                i++;
            }

            /*record the target directory*/
            while(cmd[i]!= '\0'){
                target_dir[j] = cmd[i];
                i++;
                j++;
            }
        }

    }

    /*processing the target directory*/

    /*show files and folds of current directory*/
    if(target_dir[0] == '\0')
    {       
        /*get current work directory*/
        getcwd(current_dir,sizeof(current_dir));
        /*read dir*/
        dir_list = opendir(current_dir);

        /*is NULL?*/
        if(dir_list == NULL){
            printf("\"%s\" is not a valid directory\n\n",current_dir);
            return 0;
        }

        /*show list*/
        printf("\n");
        while(filesINFO = readdir(dir_list)){
            /*I don't want to print '.' or '..' */
            if (strcmp(filesINFO->d_name,".") == 0 || strcmp(filesINFO->d_name,"..") == 0 )
            {
                continue;
            }
            
            printf("%s\n",filesINFO->d_name);

        }
        printf("\n");

        closedir(dir_list);
        return 0;

    }else{
        /*read dir*/
        dir_list = opendir(target_dir);

        /*is NULL?*/
        if(dir_list == NULL){
            printf("\"%s\" is not a valid directory\n\n",target_dir);
            return 0;
        }

        /*show list*/
        printf("\n");
        while(filesINFO = readdir(dir_list)){
            /*I don't want to print '.' or '..' */
            if (strcmp(filesINFO->d_name,".") == 0 || strcmp(filesINFO->d_name,"..") == 0 )
            {
                continue;
            }
            
            printf("%s\n",filesINFO->d_name);

        }
        printf("\n");

        closedir(dir_list);
        return 0;
    }    
    
}


/*To change the working directory*/
void changeWorkDIR(char cmd[]){
    int i=0,j=0;//index
    char target_dir[256];

    /*initialize */
    memset(target_dir,'\0',sizeof(target_dir));

    /*If first character is space ,jump through until character is not space*/
    if(cmd[0] == ' ')
    {
        while(cmd[i] == ' '){
            i++;
            /*In case of out of index*/
            if(cmd[i] == '\0'){
                break;
            }
        }
    }

    /*jump through operation and get the target directory*/
    while (cmd[i] != ' ')
    {
        i++;
        if(cmd[i] == '\0'){
            break;
        }
    }

    /*jump through character space*/
    while (cmd[i] == ' ')
    {
        i++;
        /* In case of out of index */
        if(cmd[i]=='\0'){
            break;
        }
    }
    
    /*Get the target directory*/
    while(cmd[i] != '\0'){
        target_dir[j] = cmd[i];
        i++;j++;
    }

    /*If target directory is "",execute "cd ~"*/
    if(target_dir[0] == '\0'){
        chdir("/home");
        printf("Current working directory has changed to \"/home\" \n\n");
        return;
    }
    if(chdir(target_dir) == 0){
        printf("Current working directory has changed to \"%s\"\n\n",target_dir);
    }else{
        printf("\"%s\" is not a valid directory\n\n",target_dir);
    }


}


void NewDir(char cmd[]){
    int i=0,j=0;//index
    char new_DIR[256];
    char path[256];//current working path

    /*Initialize*/
    memset(new_DIR,'\0',sizeof(new_DIR));
    memset(path,'\0',sizeof(path));

    /*jump through space*/
    if(cmd[0] == ' '){
        while (cmd[i] == ' ')
        {                  
            i++;
            /*In case of out of index*/
            if(cmd[i]== '\0'){
                break;
            }
        }
    }

    /*jump through not space*/
    while(cmd[i] != ' '){
        i++;
        if(cmd[i] == '\0'){
            break;
        }
    }

    /*jump through space to get the new directory name*/
    while(cmd[i] == ' '){
        i++;
        if(cmd[i] == '\0'){
            break;
        }
    }

    /*get the name of the new directory */
    while(cmd[i] != '\0'){
        new_DIR[j] = cmd[i];
        i++;j++;
    }

    /*If new directory name is ""*/
    if(new_DIR[0] == '\0'){
        printf("The name of the new directory cannot be \"\"\n\n");
        return;
    }

    /*get current working directory*/

    getcwd(path,sizeof(path));

    /*If new directory exist*/
    if(opendir(new_DIR) != NULL){
        printf("Directory \"%s\" already exist\n\n",new_DIR);
        return;
    }

    /* mode 0777:every one can read and write*/
    if(mkdir(new_DIR,0777) < 0){
        printf("Fail to make new directory\n\n");
    }else{
        printf("Directory was successfully made at %s\n\n",path);
    }
    
}


void RemoveDIR(char cmd[]){
    int i =0 ,j = 0;//index
    char path[256];//current working directory
    char target_dir[256];

    /*Initialize*/
    memset(target_dir,'\0',sizeof(target_dir));
    memset(path,'\0',sizeof(path));

    /*jump through space*/
    if(cmd[0] == ' '){
        while (cmd[i] == ' ')
        {                  
            i++;
            /*In case of out of index*/
            if(cmd[i]== '\0'){
                break;
            }
        }
    }

    /*jump through not space*/
    while(cmd[i] != ' '){
        i++;
        if(cmd[i] == '\0'){
            break;
        }
    }

    /*jump through space to get the directory name*/
    while(cmd[i] == ' '){
        i++;
        if(cmd[i] == '\0'){
            break;
        }
    }

    /*get the name of the directory */
    while(cmd[i] != '\0'){
        target_dir[j] = cmd[i];
        i++;j++;
    }

    if(target_dir[0] == '\0'){
        printf("Target directory cannot be \"\"\n\n");
        return;
    }

    /*If target directory doesn't exist*/
    if(opendir(target_dir) == NULL){
        printf("Directory \"%s\" doesn't exist\n\n",target_dir);
        return;
    }

    /*delete the directory*/
    if(rmdir(target_dir) < 0){
        printf("Fail to remove directory named of \"%s\"\n\n",target_dir);
    }else
    {
        getcwd(path,sizeof(path));
        printf("Directory \"%s\" has been removed from \"%s\"\n\n",target_dir,path);
    }
    
    
}



void Rename(char cmd[]){
    int i=0,j=0;
    char source[256];
    char destination[256];

    memset(source,'\0',sizeof(source));
    memset(destination,'\0',sizeof(destination));

    /*jump through space before operate code*/
    if(cmd[0] == ' '){
        while (cmd[i] == ' ')
        {
            i++;
            if(cmd[i] == '\0'){
                break;
            }
        }       
    }

    /*jump through command*/
    while (cmd[i] != ' ')
    {
        i++;
        if(cmd[i] == '\0'){
            break;
        }
    }

    /*jump through space*/
    while(cmd[i] == ' '){
        i++;
        if(cmd[i] == '\0'){
            break;
        }
    }
    

    /*get the souce file/fold name*/
    while(cmd[i] != ' '){
        source[j] = cmd[i];
        i++;j++;
        if(cmd[i] == '\0'){
            break;
        }
    }
    j=0;

    /*jump through space*/
    while(cmd[i] == ' '){
        i++;
        if(cmd[i] == '\0'){
            break;
        }
    }

    /*get destination file/fold*/
    while(cmd[i] != ' '){
        destination[j] = cmd[i];
        i++;j++;
        if(cmd[i] == '\0'){
            break;
        }
    }
    
    /*check*/
    if(source[0] == '\0'){
        printf("Missing source file/fold\n\n");
        return;
    }

    /*file or fold exist*/
    if(opendir(source) != NULL){
        /*It is a fold*/
    }else if(fopen(source,"r") != NULL){
        /*It is a file*/
    }else{
        printf("No such file or directory\n\n");
        return;
    }

    if(destination[0] == '\0'){
        printf("Missing destination file/fold\n\n");
        return;
    }

    /*execute*/
    if(rename(source,destination)<0){
        printf("Fail to change the name of \"%s\"\n\n",source);
        return;
    }else
    {
        printf("operating successfully!\n\n");
        return;
    }
    
    
}


/*copy file or directory*/
void Copy(char cmd[]){
    int i=0,j=0;//index
    char source[256];//source file or directory
    char target[256];//target file or directory

    /*Initialize*/
    memset(source,'\0',sizeof(source));
    memset(target,'\0',sizeof(target));

    /*get source file/directory*/
    if(cmd[0] == ' '){
        while(cmd[i] == ' '){
            i++;
            if(cmd[i] == '\0'){
                break;
            }
        }      
    }

    /*jump through operation*/
    while(cmd[i] != ' '){
        i++;
        if(cmd[i] == '\0'){
            break;
        }
    }

    while(cmd[i] == ' '){
        i++;
        if(cmd[i] == '\0'){
            break;
        }
    }

    while(cmd[i]!= ' '){
        source[j] = cmd[i];
        i++;j++;
        if(cmd[i] == '\0'){
            break;
        }
    }
    j=0;

    while(cmd[i] == ' '){
        i++;
        if(cmd[i] == '\0'){
            break;
        }
    }


    /*get target file/directory*/
    while(cmd[i]!=' '){
        target[j] = cmd[i];
        i++;j++;
        if(cmd[i] == '\0'){
            break;
        }
    }

    /*processing source*/
    if(source[0] == '\0'){
        printf("You must input source file/directory\n\n");
        return;
    }

    if(target[0] == '\0'){
        printf("You must input destination file/fold\n\n");
        return;
    }

    /*file or directory*/
    if(opendir(source) != NULL){
        /*copy directory*/
        CopyFold(source,target);

    }else if(fopen(source,"rb") != NULL){
        /*copy file*/
        CopyFile(source,target);

    }else{
        printf("No such file or directory named \"%s\"\n\n",source);
        return;
    }    
}

/*copy file*/
void CopyFile(char source[],char destination[]){
    char buffer[1024];//buffer zone == 1MB
    FILE *input,*output;

    /*name of the source and destination can not be the same*/
    if(strcmp(source,destination) == 0){
        printf("File \"%s\" already existed\n\n",source);
        return;
    }

    
    input = fopen(source,"rb");
    if(input == NULL){
        printf("Cannot open \"%s\"\n\n",source);
        return;
    }

    /*destination is file or directory*/
    if(opendir(destination) != NULL){
        /*get source file name and add it to the destination*/
        int i = strlen(source) - 1;
        int j = strlen(destination);

        while(i >= 0){
            if(source[i] == '/'){
                while(source[i] != '\0'){
                    destination[j] = source[i];
                    i++;j++;
                }
                break;
            }else if(i==0)
            {
                destination[j] = '/';
                j++;
                while(source[i] != '\0'){
                    destination[j] = source[i];
                    i++;j++;
                }
                break;
            }
            
            i--;
        }

        /*check destination file is existed or not*/
        if(fopen(destination,"r")!= NULL){
            printf("Destination file already existed\n\n");
            return;
        }else{
            /*create file*/
            output = fopen(destination,"wb");
            if(output == NULL){
                printf("Failed to create destination file\n\n");
                return;
            }
            /*Start copying*/
            int len;
            while( (len = fread(buffer,sizeof(char),1024,input)) >0 ){
                fwrite(buffer,sizeof(char),len,output);
            }
            printf("File has been copied successfully\n\n");

            /*close and store*/
            fclose(input);
            fclose(output);

            return;
        }

    }else{
        /*create file*/
        output = fopen(destination,"wb");
        if(output == NULL){
            printf("Failed to create destination file\n\n");
            return;
        }
        /*Start copying*/
        int len;
        while( (len = fread(buffer,sizeof(char),1024,input)) >0 ){
            fwrite(buffer,sizeof(char),len,output);
        }
        printf("File has been copied successfully\n\n");

        /*close and store*/
        fclose(input);
        fclose(output);

        return;

    }

}


/*copy fold*/
void CopyFold(char source[],char destination[]){
    char buffer[1024];//buffer zone == 1MB
    FILE *input,*output;//source file stream and target file stream
    char currentDIR[256];//store current DIR
    char dir_name[256];//get fold/directory name
    struct dirent *fileINFO;//get file and fold info from a directory
    DIR *dirINFO;//get directory info
    char temp_source[256];//temporary source fold
    char temp_destination[256];//temporary destination fold
    char temp_path[256];//temporary path
    int i=0,j = 0;//index
    int len = 0;//binary data number

    /*Initialize*/
    memset(dir_name,'\0',sizeof(dir_name));
    memset(temp_source,'\0',sizeof(temp_source));
    memset(temp_destination,'\0',sizeof(temp_destination));

    getcwd(currentDIR,sizeof(currentDIR));//get current directory

    /*open destination directory*/
    if(opendir(destination) == NULL){
        printf("Destination directory \"%s\" doesn't exist\n\n",destination);
        return;
    }

    /*open source directory*/
    if(opendir(source) == NULL){
        printf("Source directory \"%s\" doesn't exist\n\n",source);
        return;
    }

    //Turn reletive path into absolute path
    /*formal parameter "source" is a pointer,not array,using keyword "sizeof" is just caculate the size of this pointer,
    we could not use "sizeof" to caculate the size of array "source"*/
    if(source[0] != '/'){
        chdir(source);
        memset(source,'\0',sizeof(source));
        getcwd(temp_path,sizeof(temp_path));
        strcpy(source,temp_path);
        chdir(currentDIR);
    }
    if(destination[0] != '/'){
        chdir(destination);
        memset(destination,'\0',sizeof(destination));
        getcwd(temp_path,sizeof(temp_path));
        strcpy(destination,temp_path);
        chdir(currentDIR);
    }

    //get source fold name
    i = strlen(source)-1;

    while(i>= 0){
        if(source[i] == '/'){
            i++;
            while(source[i] != '\0'){
                dir_name[j] = source[i];
                i++;j++;
            }
            break;
        }

        i--;
    }
    
    
    //change work directory to destination
    chdir(destination);    
    //is source fold/directory existed in destination fold/directory
    if(opendir(dir_name)==NULL){
        mkdir(dir_name,0777);
        printf("Creating new fold \"%s/%s...\"\n",destination,dir_name);
        chdir(dir_name);
    }else
    {
        printf("Fold \"%s/%s\" already existed\n",destination,dir_name);
        chdir(dir_name);
    }
    

    //open source fold
    dirINFO = opendir(source);
    
    if(dirINFO == NULL){
        printf("Cannot open source directory \"%s\"\n",source);
        return;
    }

    /*get file and fold info from the source fold*/
    while(fileINFO = readdir(dirINFO)){
        if(strcmp(fileINFO->d_name,".")==0 || strcmp(fileINFO->d_name,"..") == 0){
            continue;
        }

        /*if destination fold has a fold name as same as a fold of the source fold ,check this fols existed or not,and if
        this fold existed, jump it in case of out of stamp(create this fold over and over again ....)*/
        if(strcmp(dir_name,fileINFO->d_name) == 0){
            if(opendir(dir_name) != NULL){
                    continue;
            }
        }
        
        chdir(source);

        /*Is fold/directory?*/
        if(opendir(fileINFO->d_name)!= NULL){
            i=0;j=0;
            strcpy(temp_source,source);
            strcpy(temp_destination,destination);

            j = strlen(temp_source);
            temp_source[j] = '/';
            j++;

            while(fileINFO->d_name[i] != '\0'){
                temp_source[j] = fileINFO->d_name[i];
                i++;j++;
            }

            j = strlen(temp_destination);
            i = 0;
            temp_destination[j] = '/';
            j++;

            while(dir_name[i] != '\0'){
                temp_destination[j] = dir_name[i];
                i++;j++;
            }

            //call function itself
            CopyFold(temp_source,temp_destination);

        }else{
            chdir(destination);
            chdir(dir_name);
            /*copy file*/

            /*is file existed in destination?*/
            output = fopen(fileINFO->d_name,"rb");
            if(output!=NULL){
                printf("File \"%s/%s\" already existed!\n",source,fileINFO->d_name);
                fclose(output);
                continue;
            }

            /*starting copy*/
            /*open source file*/
            chdir(source);
            input = fopen(fileINFO->d_name,"rb");
            if(input == NULL){
                printf("Failed to open source file \"%s/%s\"\n",source,fileINFO->d_name);
                continue;
            }

            /*create destination file*/
            chdir(destination);
            chdir(dir_name);
            output = fopen(fileINFO->d_name,"wb");
            if(output == NULL){
                printf("Error:Could not create file\"%s/%s/%s\"\n",destination,dir_name,fileINFO->d_name);
            }

            /*copy operation*/
            len = 0;
            while(len = fread(buffer,sizeof(char),sizeof(buffer),input)){
                fwrite(buffer,sizeof(char),len,output);
            }

            /*close and store file*/
            fclose(input);
            fclose(output);

            printf("Succeessfully copied file \"%s/%s\"\n",source,fileINFO->d_name);
        }
    }

    chdir(currentDIR);//return to the previous directory/fold
}



void Find(char cmd[]){
    int i=0,j=0;//index
    char currentDIR[256];//get current directory
    char dir_name[256];//Where to search
    char file_or_fold_name[256];//which file/fold you want to search
    char second_parameter[10];//get second word and check it is "-name" or not

    getcwd(currentDIR,sizeof(currentDIR));

    /*Initialize*/
    memset(dir_name,'\0',sizeof(dir_name));
    memset(file_or_fold_name,'\0',sizeof(file_or_fold_name));
    memset(second_parameter,'\0',sizeof(second_parameter));

    /*proccessing userinput*/
    while(cmd[i] == ' '){
        i++;
        if(cmd[i] == '\0'){
            break;
        }
    }
    /*jump through operation word*/
    while(cmd[i] != ' '){
        i++;
        if(cmd[i] == '\0'){
            break;
        }
    }

    while(cmd[i] == ' '){
        i++;
        if(cmd[i] == '\0'){
            break;
        }
    }

    /*get directory name*/
    while(cmd[i] != ' '){
        dir_name[j] = cmd[i];
        i++;j++;
        if(cmd[i] == '\0'){
            break;
        }
    }

    while(cmd[i] == ' '){
        i++;
        if(cmd[i] == '\0'){
            break;
        }
    }
    /*get second parameter if it existed*/
    j = 0;
    while(cmd[i] != ' '){
        second_parameter[j] = cmd[i];
        i++;j++;
        if(cmd[i] == '\0'){
            break;
        }
    }

    while(cmd[i] == ' '){
        i++;
        if(cmd[i] == '\0'){
            break;
        }
    }
    
    /*get file/fold name if it existed*/
    j = 0;
    while(cmd[i] != '\0'){
        file_or_fold_name[j] = cmd[i];
        i++;j++;
        if(cmd[i] == '\0'){
            break;
        }
    }


    /*check directory,second parameter and file/fold name*/
    if(strcmp(dir_name,"") == 0){
        /*search  all file or fold of the current directory*/
        getcwd(dir_name,sizeof(dir_name));

        do_find(dir_name,"");
    }

    /*second_parameter is "-name" and dirname is not ""*/
    if(strcmp(second_parameter,"") !=0 && strcmp(second_parameter,"-name") == 0){
        if(strcmp(file_or_fold_name,"")!=0){

            do_find(dir_name,file_or_fold_name);

        }else
        {
            printf("Missing file or fold name after \"-name\"\n\n");
            return;
        }
        
    }else
    {
        /*execute*/
        do_find(dir_name,"");
        if(strcmp(file_or_fold_name,"") != 0){
            printf("No such file or directory named \"%s\"\n\n",file_or_fold_name);
        }        
    }
    
}


void do_find(char dirName[],char file_or_fold_name[]){
    DIR *dirINFO;
    struct dirent *fileINFO;
    int i = 0,j = 0;//index
    char temp_dir[256];//store temparory path of the file or fold


    /*if file_or_fold is "",output every file or fold location*/
    if(strcmp(file_or_fold_name,"") == 0){

        dirINFO = opendir(dirName);
        if(dirINFO == NULL){
            printf("Cannot open directory named \"%s\"\n",dirName);
            return;
        }

        /*output info*/
        while(fileINFO = readdir(dirINFO)){
            if(strcmp(fileINFO->d_name,".") == 0 || strcmp(fileINFO->d_name,"..") == 0){
                continue;
            }

            /*clear out temp_dir*/
            memset(temp_dir,'\0',sizeof(temp_dir));
            //add "/****" to the end of char array "dir_name"
            strcpy(temp_dir,dirName);
            i = 0;
            j = strlen(temp_dir);
            temp_dir[j] = '/';
            j++;

            while(fileINFO->d_name[i] != '\0'){
                 temp_dir[j] = fileINFO->d_name[i];
                i++;j++;
            }

            /*print info*/
            printf("%s\n",temp_dir);

            /*check  is it a directory/fold or not*/
            if(opendir(fileINFO->d_name)!=NULL){
                
                /*check this directory and output its info*/
                do_find(temp_dir,"");
            }
            
        }
    /*output every file or fold named like the value in "file_or_fold_name"*/
    }else{

        dirINFO = opendir(dirName);
        if(dirINFO == NULL){
            printf("Cannot open directory named \"%s\"\n",dirName);
            return;
        }

        /*output info*/
        while(fileINFO = readdir(dirINFO)){
            if(strcmp(fileINFO->d_name,".") == 0 || strcmp(fileINFO->d_name,"..") == 0){
                continue;
            }

            /*check the name of file or fold is that we want to find or not*/
            if(strcmp(file_or_fold_name,fileINFO->d_name) != 0){
                continue;
            }

            /*clear out temp_dir*/
            memset(temp_dir,'\0',sizeof(temp_dir));
            //add "/****" to the end of char array "dir_name"
            strcpy(temp_dir,dirName);
            i = 0;
            j = strlen(temp_dir);
            temp_dir[j] = '/';
            j++;

            while(fileINFO->d_name[i] != '\0'){
                temp_dir[j] = fileINFO->d_name[i];
                i++;j++;
            }

            /*print info*/
            printf("%s\n",temp_dir);

            /*check  is it a directory/fold or not*/
            if(opendir(fileINFO->d_name)!=NULL){
                
                /*check this directory and output its info*/
                do_find(temp_dir,fileINFO->d_name);
            }
        }
            
    }
}
