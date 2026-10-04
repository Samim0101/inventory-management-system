
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

int main()
{
    Product products[1];

    printf("----- Product Details -----\n");

    printf("Enter your product ID: ");
    scanf("%d", &products[0].product_id);
    getchar();

    printf("Enter your product name: ");
    fgets(products[0].product_name, sizeof(products[0].product_name), stdin);

    products[0].product_name[strcspn(products[0].product_name, "\n")] = '\0';

    printf("Enter your quantity: ");
    scanf("%d", &products[0].quantity);

    printf("Enter your price: ");
    scanf("%f", &products[0].price);

    display_product(products, 1);
    return 0;
}