// Name:Taleen Bayatneh // ID:1211305 // section: 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define lineLength 200

typedef struct node *Node;
struct node
{
    char town[50];//key
    char district[50];
    int population;
    int elevation;
    char HasManucipility[5];
    Node Left;
    Node Right;
    int height;

};
///////////////////////
typedef struct hash *Hash;
struct hash
{
    char Town[50];//key
    char district[50];
    int Population;
    int Elevation;
    char Has_Manucipility[5];
    int busy;

};
///////////////////////////////////////Hash
///////////////////////
void create_hash_table();
void insert_to_table(char *Town, char *district, int Population, int Elevation, char *Has_Municipality);
unsigned int hash_Function(char *Town);
void search_and_print(char *Town);
void delete_from_table(char *Town);
void print_table();
void print_size_Lfactor(int num_lines);
void savetofile(FILE *towns);
int is_Prime(int num);
int calculate_size(int num);
void load(char *Tline);
///////////////////////
int size ;
Hash *hash_table;

///////////////////////

///////////////////////////////////////AVL Tree
//AVLTree createNode(char *town,char *district,int population,int elevation,char *HasManucipility);
Node insert_to_tree(char *town, char *district, int population, int elevation, char *HasManucipility, Node root);
Node delete_from_tree(Node root, char *town);
int balance(Node root);
Node makeitEmpty(Node root);
Node Findmin(Node root);
Node Findmax(Node root);
int max(int right_hb, int left_hb);
Node LeftSingleRotation(Node r2);
Node RightSingleRotation(Node r1);
Node LeftDoubleRotate(Node r3);
Node RightDoubleRotate(Node r1);

///////////////////////
Node load_to_tree(Node root, char *line);
void list_by_population(Node root, int num);
void list_by_municipalities(Node root, int choice);
void save_to_file(Node root, FILE *towns);
Node searchAndupdate(Node root, char *town, int c2);
void printInOrder(Node root);

//////////////////////
int main()
{
    int c,c2,c4,c5 ;
    char line[lineLength],townlines[lineLength];
    Node root = NULL ;
    root = makeitEmpty(root);
    Node search_node = NULL;
    search_node = makeitEmpty(search_node);
    char town[50];//key
    char district[50];
    int population;
    int elevation;
    char HasManucipility[5];

    char H_town[50];//key
    char H_district[50];
    int H_population;
    int H_elevation;
    char H_HasManucipility[5];

    char ttown[50],H_ttown[50];
    char toown[50],H_toown[50];
    int popu_num;
    char n_line;
    int num_lines =0 ;

    do
    {
        printf("\nchoose one of the following :\n");
        printf("1. Read the file and load the data.\n");
        printf("2. Insert a new town with all its associated information.\n");
        printf("3. search about a town to update its information (if found).\n");
        printf("4. List the towns in alphabetical order with their associated information.\n");
        printf("5. List all towns that have population greater than the number you enter.\n");
        printf("6. List all towns that have municipalities or not.\n");
        printf("7. Delete a town from the data.\n");
        printf("8. Save all information to the towns file.\n");
        printf("9. create the hash using the data from towns file.\n");
        printf("10. Exit\n");
        scanf("%d",&c);
        FILE* districts;
        FILE* towns;

        switch (c)
        {
        case 1 ://Read the file and load the data.
            districts = fopen("C:\\Users\\dell\\Desktop\\data_structure\\P3_1211305_taleenbayatneh_1\\districts.txt","r");
            if (districts == NULL)
            {
                printf("error opening file");
            }
            while(fgets(line,lineLength,districts)!= NULL)
            {
                root = load_to_tree(root,line);

            }
            printInOrder(root);
            fclose(districts);

            break;

        case 2 ://Insert a new town with all its associated information.
            printf("enter the town you want to insert : ");
            scanf("%49s",town);

            printf("\nnow enter the information for that town :\n");

            printf("district : ");
            scanf("%49s",district);

            printf("\npopulation : ");
            scanf("%d",&population);

            printf("\nelevation : ");
            scanf("%d",&elevation);

            printf("\nhas municipality : ");
            scanf("%4s",HasManucipility);


            /*printf("town: %s\n", town);
            printf("district: %s\n", district);
            printf("population: %d\n", population);
            printf("elevation: %d\n", elevation);
            printf("has municipality: %s\n", HasManucipility);*/
            root=insert_to_tree(town,district,population,elevation,HasManucipility,root);
            printInOrder(root);

            break;

        case 3 ://search about a town to update its information (if found).

            printf("enter the town you want to update its info : ");
            scanf("%s",ttown);
            printf("choose one of the following to update: \n");
            printf("1. Update the population\n");
            printf("2. Update the elevation\n");
            printf("3. Update if it has a municipality or not\n");
            scanf("%d",&c2);
            search_node = searchAndupdate(root,ttown,c2);
            if (search_node != NULL)
                root = insert_to_tree(search_node->town,search_node->district,search_node->population,search_node->elevation,search_node->HasManucipility,root);

            break;

        case 4 ://List the towns in alphabetical order with their associated information.
            printInOrder(root);

            break;

        case 5 ://List all towns that have population greater than the number you enter.
            printf("enter a number to display all the towns that have population more that it :  ");
            scanf("%d",&popu_num);
            list_by_population(root,popu_num);

            break;

        case 6 ://List all towns that have municipalities or not.
            printf("choose one of the following to display: \n");
            printf("1. display the towns that have a municipality\n");
            printf("2. display the towns that do not have a municipality\n");
            scanf("%d",&c4);
            list_by_municipalities(root,c4);

            break;

        case 7 ://Delete a town from the data.
            printf("enter the town you want to delete : ");
            scanf("%s",toown);
            delete_from_tree(root,toown);

            break;

        case 8 ://Save all information to the file.
            towns = fopen("C:\\Users\\dell\\Desktop\\data_structure\\P3_1211305_taleenbayatneh_1\\towns.txt","w");
            if (towns == NULL)
            {
                printf("error opening file");
            }
            save_to_file(root,towns);
            fclose(towns);

            break;

        case 9 ://display hash menu
            do
            {
                printf("\nchoose one of the following :\n");
                printf("1.load the data and create the hash table.\n");
                printf("2. print the entire table to the screen including empty spots.\n");
                printf("3. Print the size of hash table and the load factor.\n");
                printf("4. Insert a new record into the hash table.\n");
                printf("5. Search for a specific town and print the number of collisions to reach the town.\n");
                printf("6. Delete a specific record.\n");
                printf("7. Save the data back to the towns file.\n");
                printf("8. Back to the main menu.\n");
                scanf("%d",&c5);

                switch (c5)
                {
                case 1:
                    towns = fopen("C:\\Users\\dell\\Desktop\\data_structure\\P3_1211305_taleenbayatneh_1\\towns.txt", "r");
                    if (towns == NULL)
                    {
                        printf("error opening file");
                    }

                    while (fgets(townlines, lineLength, towns))
                    {
                        load(townlines);

                    }
                    while ((n_line = fgetc(towns)) != EOF)
                    {
                        if (n_line == '\n')
                            num_lines++;
                    }

                    size=calculate_size(num_lines);
                    create_hash_table();

                    break;

                case 2 ://print the entire table to the screen including empty spots
                    print_table();
                    break;

                case 3 ://Print the size of hash table and the load factor
                    print_size_Lfactor(num_lines);
                    break;

                case 4 ://Insert a new record into the hash table
                    printf("enter the town you want to insert : ");
                    scanf("%49s",H_town);

                    printf("\nnow enter the information for that town :\n");

                    printf("district : ");
                    scanf("%49s",H_district);

                    printf("\npopulation : ");
                    scanf("%d",&H_population);

                    printf("\nelevation : ");
                    scanf("%d",&H_elevation);

                    printf("\nhas municipality : ");
                    scanf("%4s",H_HasManucipility);

                    insert_to_table(H_town,H_district,H_population,H_elevation,H_HasManucipility);

                    break;

                case 5 ://Search for a specific town and print the number of collisions to reach the town
                    printf("enter the town you want to update its info : ");
                    scanf("%s",H_ttown);

                    search_and_print(H_ttown);

                    break;

                case 6 ://Delete a specific record
                    printf("enter the town you want to delete : ");
                    scanf("%s",H_toown);

                    delete_from_table(H_toown);
                    break;

                case 7 ://Save the data back to the towns file
                    savetofile(towns);
                    break;

                case 8 ://exit the menu
                    //printf("done");
                    break;

                default:
                    printf("invalid choice,please enter from 1-7");
                }


            }
            while(c5 != 8);

            fclose(towns);
            //printf("done");
            break;

        case 10 ://exit
            exit(0);
            break;

        default:
            printf("invalid choice,please enter from 1-10");//if the user enter another choice
        }

    }
    while(c != 10);

    return 0;
}
///////////////////////////////////////Hash
/////////////////create hash table
void create_hash_table(FILE* towns)
{
    hash_table = (Hash *)malloc(size * sizeof(struct hash));
    for (int i = 0; i < size; i++)
    {
        hash_table[i] = (Hash)malloc(sizeof(struct hash));
        hash_table[i]->busy = 0; // Initialize all slots as empty
    }

}
//////////////////
void insert_to_table(char *Town,char* district,int Population,int Elevation,char *Has_Municipality)
{
    unsigned int index = hash_Function(Town);
    int originalIndex = index;
    int collisions = 0;

    while (hash_table[index]->busy)
    {
        if (strcmp(hash_table[index]->Town, Town) == 0)
        {
            // Town already exists, update the information
            strcpy(hash_table[index]->district, district);
            hash_table[index]->Population = Population;
            hash_table[index]->Elevation = Elevation;
            strcpy(hash_table[index]->Has_Manucipility, Has_Municipality);
            return;
        }
        index = (index + 1) % size; // Linear probing
        collisions++;
        if (index == originalIndex)
        {
            printf("Hash table is full!\n");
            return;
        }
    }

    // Insert new record
    strcpy(hash_table[index]->Town, Town);
    strcpy(hash_table[index]->district, district);
    hash_table[index]->Population = Population;
    hash_table[index]->Elevation = Elevation;
    strcpy(hash_table[index]->Has_Manucipility, Has_Municipality);
    hash_table[index]->busy = 1;


}
//////////////////
unsigned int hash_Function(char *Town)
{
    unsigned int hash = 0;
    int len = (strlen(Town) > 5) ? 5 : strlen(Town); // Use first 5 characters
    for (int i = 0; i < len; i++)
    {
        hash = (hash << 5) + Town[i];
        if (hash < 0)
            hash += size;
    }
    return hash % size;

}
//////////////////
void search_and_print(char *Town)
{
    unsigned int index = hash_Function(Town);
    int originalIndex = index;
    int collisions = 0;

    while (hash_table[index]->busy)
    {
        if (strcmp(hash_table[index]->Town, Town) == 0)
        {
            printf("Town: %s\n", hash_table[index]->Town);
            printf("District: %s\n", hash_table[index]->district);
            printf("Population: %d\n", hash_table[index]->Population);
            printf("Elevation: %d\n", hash_table[index]->Elevation);
            printf("Has Municipality: %s\n", hash_table[index]->Has_Manucipility);
            printf("Collisions: %d\n", collisions);
            return;
        }
        index = (index + 1) % size; // Linear probing
        collisions++;
        if (index == originalIndex)
        {
            printf("Town not found!\n");
            return;
        }
    }

    printf("Town not found!\n");

}
//////////////////
void delete_from_table(char *Town)
{
    unsigned int index = hash_Function(Town);
    int originalIndex = index;

    while (hash_table[index]->busy)
    {
        if (strcmp(hash_table[index]->Town, Town) == 0)
        {
            hash_table[index]->busy = 0; // Mark as deleted
            printf("Town deleted successfully!\n");
            return;
        }
        index = (index + 1) % size; // Linear probing
        if (index == originalIndex)
        {
            printf("Town not found!\n");
            return;
        }
    }

    printf("Town not found!\n");

}
//////////////////
void print_table()
{
    for (int i = 0; i < size; i++)
    {
        if (hash_table[i]->busy)
        {
            printf("%s:%s:%d:%d:%s\n", hash_table[i]->Town, hash_table[i]->district, hash_table[i]->Population, hash_table[i]->Elevation, hash_table[i]->Has_Manucipility);
        }
        else
        {
            printf("Empty\n"); // Print empty spots
        }
    }
}
//////////////////
void print_size_Lfactor(int num_lines)
{
    printf("size of hash table:%d\n",size);
    printf(" the load factor:%.2f\n",(float)num_lines/size);
}
//////////////////
void savetofile(FILE* towns)
{
    for (int i=0; i<size; i++)
    {
        if (hash_table[i]->busy)
        {
            fprintf(towns,"%s:%s:%d:%d:%s\n",hash_table[i]->district,hash_table[i]->Town,hash_table[i]->Population,hash_table[i]->Elevation,hash_table[i]->Has_Manucipility);
        }
    }
}
//////////////////
void load(char *Tline)
{
    char town[50];//key
    char district[50];
    int population=0;
    int elevation=0;
    char hasManucipility[5];

    Tline[strcspn(Tline, "\n")] = '\0';

    char *token = strtok(Tline, ":");
    if (token)
        strcpy(district, token);

    token = strtok(NULL, ":");
    if (token)
        strcpy(town, token);

    token = strtok(NULL, ":");
    if (token)
        population = atoi(token);

    token = strtok(NULL, ":");
    if (token)
        elevation = atoi(token);

    token = strtok(NULL, ":");
    if (token)
        strcpy(hasManucipility, token);

    insert_to_table(town,district,population,elevation,hasManucipility);

}
//////////////////
int calculate_size(int num)
{
    num=num*2;
    while (!is_Prime(num))
    {
        num++;
    }
    //printf("%d",num);
    return num;
}
//////////////////
int is_Prime(int num)
{
   if (num <= 1)
        return 0;
    if (num <= 3)
        return 1;
    if (num % 2 == 0 || num % 3 == 0)
        return 0;
    for (int i = 5; i * i <= num; i += 6)
    {
        if (num % i == 0 || num % (i + 2) == 0)
            return 0;
    }
    return 1;

}
///////////////////////////////////////AVL Tree
/////////////////
void save_to_file(Node root,FILE* towns)
{
    if( root != NULL)
    {
        save_to_file(root->Left,towns);
        fprintf(towns,"%s:%s:%d:%d:%s\n", root->district,root->town,root->population,root->elevation,root->HasManucipility);
        save_to_file(root->Right,towns);
    }


}
/////////////////
void list_by_municipalities(Node root, int choice)
{
    int c5;
    if( root != NULL)
    {
        if(choice==1)
        {
            list_by_municipalities(root->Left,choice);
            if(strcmp(root->HasManucipility,"yes")== 0)
                printf("%s : %s : %d : %d : %s \n", root->town,root->district,root->population,root->elevation,root->HasManucipility);
            list_by_municipalities(root->Right,choice);
        }
        else if (choice==2)
        {
            list_by_municipalities(root->Left,choice);
            if(strcmp(root->HasManucipility,"No")== 0)
                printf("%s : %s : %d : %d : %s \n", root->town,root->district,root->population,root->elevation,root->HasManucipility);
            list_by_municipalities(root->Right,choice);
        }
        else
        {
            printf("this option is not valid please enter 1 or 2 : ");
            scanf("%d",&c5);
            list_by_municipalities(root,c5);

        }

    }

}
/////////////////
void list_by_population(Node root, int num)
{
    if( root != NULL)
    {
        list_by_population(root->Left,num);
        if(root->population > num)
            printf("%s : %s : %d : %d : %s \n", root->town,root->district,root->population,root->elevation,root->HasManucipility);
        list_by_population(root->Right,num);
    }

}
/////////////////
Node load_to_tree(Node root,char *line)
{
    char town[50];//key
    char district[50];
    int population=0;
    int elevation=0;
    char hasManucipility[5];

    line[strcspn(line, "\n")] = '\0';

    char *token = strtok(line, ":");
    if (token)
        strcpy(district, token);

    token = strtok(NULL, ":");
    if (token)
        strcpy(town, token);

    token = strtok(NULL, ":");
    if (token)
        population = atoi(token);

    token = strtok(NULL, ":");
    if (token)
        elevation = atoi(token);

    token = strtok(NULL, ":");
    if (token)
        strcpy(hasManucipility, token);

    //printf("District: %s\t",district);
    //printf("Town: %s\t",town);
    //printf("Population: %d\t",population);
    //printf("Elevation: %d\t",elevation);
    //printf("Has Municipality: %s\n",hasManucipility);
    //printInOrder(root);
    root = insert_to_tree(town,district,population,elevation,hasManucipility,root);
    //printf("5");
    return root;

}
/////////////////insert a new node to the trees
Node insert_to_tree(char* town,char* district,int population,int elevation,char* HasManucipility,Node root)
{
    //printInOrder(root);
    //printf("11\n");
    if(root == NULL)
    {
        //printf("12\n");
        root = malloc(sizeof(struct node));
        if(root == NULL)
            printf("out of space");
        else
        {
            //printf("13\n");
            strcpy(root->district,district);
            strcpy(root->HasManucipility,HasManucipility);
            strcpy(root->town,town);
            root->elevation = elevation;
            root->population = population;
            root->height = 0;
            root->Left = NULL;
            root->Right = NULL;
        }
        //printf("1\n");
    }

    int result = strcmp(town, root->town);
    if(result < 0)
    {
        //printf("2\n");
        root->Left = insert_to_tree(town,district,population,elevation,HasManucipility,root->Left);
        if(balance(root->Left) - balance(root->Right) == 2)
            if(strcmp(town,root->Left->town) < 0)
                root = LeftSingleRotation(root);
            else
                root = LeftDoubleRotate(root);
    }
    else if(result > 0)
    {
        //printf("3\n");
        root->Right = insert_to_tree(town,district,population,elevation,HasManucipility, root->Right);
        if(balance(root->Right) - balance(root->Left) == 2 )
            if(strcmp(town,root->Right->town) > 0)
                root = RightSingleRotation(root);
            else
                root = RightDoubleRotate(root);
    }
    else
    {
        strcpy(root->district,district);
        strcpy(root->HasManucipility,HasManucipility);
        strcpy(root->town,town);
        root->elevation = elevation;
        root->population = population;
    }

    root->height = max(balance(root->Right), balance(root->Left)) + 1;
    //printf("4\n");
    return root;
}
/////////////////
Node delete_from_tree(Node root, char *town)
{
    if (root == NULL)
    {
        printf("Town not found in the data.\n");
        return root;
    }

    // Search for the node to delete
    int cmp = strcmp(town, root->town);

    if (cmp < 0)
    {
        // Town is in the left subtree
        root->Left = delete_from_tree(root->Left, town);
    }
    else if (cmp > 0)
    {
        // Town is in the right subtree
        root->Right = delete_from_tree(root->Right, town);
    }
    else
    {
        // Town is found
        if (root->Left == NULL || root->Right == NULL)
        {
            // Node has one child or no child
            Node temp = root->Left ? root->Left : root->Right;

            if (temp == NULL)
            {
                // No child
                temp = root;
                root = NULL;
            }
            else
            {
                // One child
                *root = *temp; // Copy the contents of the non-empty child
            }

            free(temp);
        }
        else
        {
            // Node has two children
            Node temp = Findmin(root->Right); // Find the smallest node in the right subtree
            strcpy(root->town, temp->town);
            strcpy(root->district, temp->district);
            root->population = temp->population;
            root->elevation = temp->elevation;
            strcpy(root->HasManucipility, temp->HasManucipility);

            // Delete the inorder successor
            root->Right = delete_from_tree(root->Right, temp->town);
        }
    }

    // If the tree had only one node, return
    if (root == NULL)
    {
        return root;
    }

    // Update height of the current node
    root->height = 1 + max(balance(root->Left), balance(root->Right));

    // Rebalance the tree
    int balanceFactor = balance(root);

    // Left Heavy
    if (balanceFactor > 1)
    {
        if (balance(root->Left) >= 0)
        {
            return RightSingleRotation(root);
        }
        else
        {
            return LeftDoubleRotate(root);
        }
    }

    // Right Heavy
    if (balanceFactor < -1)
    {
        if (balance(root->Right) <= 0)
        {
            return LeftSingleRotation(root);
        }
        else
        {
            return RightDoubleRotate(root);
        }
    }

    return root;
}
/////////////////search about a town in the tree
Node searchAndupdate(Node root,char* town,int c2)
{
    int populat;
    int elevat;
    char Has_Manucipility[5];
    int c3;
    Node sear_node = root ;
    if(sear_node == NULL)
    {
        printf("the town not found.\n");
        return sear_node;
    }

    if(strcmp(town,sear_node->town) < 0)
    {
        return searchAndupdate(sear_node->Left,town,c2);
        //sear_node=insert_to_tree(sear_node->town,root->district,root->population,root->elevation,root->HasManucipility,root);
    }

    else if(strcmp(town,sear_node->town) > 0)
    {
        return searchAndupdate(sear_node->Right,town,c2);
        //sear_node=insert_to_tree(sear_node->town,sear_node->district,sear_node->population,root->elevation,root->HasManucipility,root);
    }

    else
    {
        if (c2 == 1)
        {
            printf("enter the new population : ");
            scanf("%d",&populat);
            sear_node->population = populat;
            printf("your data has been updated");

        }
        else if (c2 == 2)
        {
            printf("enter the new elevation : ");
            scanf("%d",&elevat);
            sear_node->elevation = elevat;
            printf("your data has been updated");

        }
        else if(c2== 3)
        {
            printf("enter if it has a municipality or not : ");
            scanf("%s",Has_Manucipility);
            strcpy(sear_node->HasManucipility,Has_Manucipility);
            printf("your data has been updated");

        }
        else
        {

            printf("this option is not valid please enter 1 or 2 or 3 : ");
            scanf("%d",&c3);
            return searchAndupdate(sear_node,town,c3);

        }
        return sear_node;

    }

}
/////////////////get the balance for a node in the tree
int balance(Node r)
{
    if( r == NULL )
        return -1;
    else
        return r->height;
}
/////////////////
void printInOrder(Node root)
{
    if( root != NULL)
    {
        printInOrder( root->Left );
        printf("%s : %s : %d : %d : %s \n", root->district,root->town,root->population,root->elevation,root->HasManucipility);
        printInOrder( root->Right );
    }

}
/////////////////free all the data in the tree
Node makeitEmpty(Node root)
{
    if(root != NULL)
    {
        makeitEmpty(root->Left);
        makeitEmpty(root->Right);
        free(root);
    }
    return NULL;
}
/////////////////find the minimum town in the tree by going to the left until we get null
Node Findmin(Node root)
{
    if(root == NULL)
        return NULL;
    else if(root->Left == NULL)
        return root;
    else
        return Findmin(root->Left);
}
/////////////////find the maximum town in the tree by going to the right until we get null
Node Findmax(Node root)
{
    if( root != NULL )
        while( root->Right != NULL )
            root = root->Right;

    return root;
}
/////////////////get the maximum hight value to find the balance for a node in the tree
int max(int right_hb, int left_hb)
{

    if (left_hb > right_hb)
        return left_hb;
    else
        return right_hb;

}
/////////////////
Node LeftSingleRotation(Node r2)
{
    Node r1;

    r1 = r2->Left;
    r2->Left = r1->Right;
    r1->Right = r2;

    r2->height = max(balance(r2->Left),balance(r2->Right)) + 1;
    r1->height = max(balance(r1->Left),r2->height) + 1;

    return r1;
}
/////////////////
Node RightSingleRotation(Node r1)
{
    Node r2;

    r2 = r1->Right;
    r1->Right = r2->Left;
    r2->Left = r1;

    r1->height = max(balance(r1->Left), balance(r1->Right)) + 1;
    r2->height = max(balance(r2->Right),r1->height) + 1;

    return r2;
}
/////////////////
Node LeftDoubleRotate(Node r3)
{
    r3->Left = RightSingleRotation(r3->Left);
    return LeftSingleRotation(r3);
}
/////////////////
Node RightDoubleRotate(Node r1)
{
    r1->Right = LeftSingleRotation(r1->Right);
    return RightSingleRotation(r1);
}
/////////////////
