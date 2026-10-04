
#include <stdio.h>
#include <string.h>

typedef struct
{
    int product_id;
    char product_name[50];
    int quantity;
    float price;
} Product;

void display_product(Product products[], int product_count)
{
    for (int i = 0; i < product_count; i++)
    {
        printf("=========================\n");
        printf("     PRODUCT DETAILS\n");
        printf("=========================\n");

        printf("PRODUCT ID: %d\n", products[i].product_id);
        printf("PRODUCT NAME: %s\n", products[i].product_name);
        printf("PRODUCT QUANTITY: %d\n", products[i].quantity);
        printf("PRODUCT PRICE: %.2f\n", products[i].price);
    }
}

int save_product(Product product)
{
    FILE *file = fopen("../data/products.dat", "ab");

    if (file == NULL)
    {
        printf("Error opening file!\n");
        return 0;
    }

    size_t result = fwrite(&product, sizeof(Product), 1, file);

    if (result != 1)
    {
        printf("Error saving product!\n");
        fclose(file);
        return 0;
    }

    fclose(file);

    printf("Product saved successfully!\n");
    return 1;
}

int add_product(Product products[], int *product_count)
{
    if (*product_count >= 100)
    {
        printf("Inventory is full!\n");
        return 0;
    }

    Product product;

    printf("\n----- Add Product -----\n");

    printf("Enter product ID: ");
    if (scanf("%d", &product.product_id) != 1)
        return 0;

    getchar();

    printf("Enter product name: ");
    if (fgets(product.product_name,
              sizeof(product.product_name), stdin) == NULL)
        return 0;

    product.product_name[strcspn(product.product_name, "\n")] = '\0';

    printf("Enter quantity: ");
    if (scanf("%d", &product.quantity) != 1)
        return 0;

    printf("Enter price: ");
    if (scanf("%f", &product.price) != 1)
        return 0;

    if (save_product(product))
    {
        products[*product_count] = product;
        (*product_count)++;

        printf("Product added successfully!\n");
        return 1;
    }

    return 0;
}

int main()
{
    Product products[100];
    int product_count = 0;
    int choice;

    while (1)
    {
        printf("\n===== INVENTORY MANAGEMENT SYSTEM =====\n");
        printf("1. Add Product\n");
        printf("2. Display Products\n");
        printf("3. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            add_product(products, &product_count);
            break;

        case 2:
            display_product(products, product_count);
            break;

        case 3:
            printf("Exiting program...\n");
            return 0;

        default:
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}