
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

int main()
{
    Product products[1];

    printf("----- Add Product -----\n");

    printf("Enter your product ID: ");
    if (scanf("%d", &products[0].product_id) != 1)
    {
        printf("Invalid product ID!\n");
        return 1;
    }
    getchar();

    printf("Enter your product name: ");
    if (fgets(products[0].product_name,
              sizeof(products[0].product_name), stdin) == NULL)
    {
        printf("Error reading product name!\n");
        return 1;
    }

    products[0].product_name[strcspn(products[0].product_name, "\n")] = '\0';

    printf("Enter your quantity: ");
    if (scanf("%d", &products[0].quantity) != 1)
    {
        printf("Invalid quantity!\n");
        return 1;
    }

    printf("Enter your price: ");
    if (scanf("%f", &products[0].price) != 1)
    {
        printf("Invalid price!\n");
        return 1;
    }

    if (save_product(products[0]))
    {
        display_product(products, 1);
    }

    return 0;
}