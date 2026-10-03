
#include <stdio.h>
#include <string.h>

typedef struct
{
    int product_id;
    char product_name[50];
    int quantity;
    float price;
} Product;

int main()
{
    Product product;

    printf("----- Product Details -----\n");

    printf("Enter your product ID: ");
    scanf("%d", &product.product_id);
    getchar();

    printf("Enter your product name: ");
    fgets(product.product_name, sizeof(product.product_name), stdin);
    
    product.product_name[strcspn(product.product_name, "\n")] = '\0';

    printf("Enter your quantity: ");
    scanf("%d", &product.quantity);

    printf("Enter your price: ");
    scanf("%f", &product.price);

    printf("\n----- Product Information -----\n");
    printf("Product ID: %d\n", product.product_id);
    printf("Product Name: %s\n", product.product_name);
    printf("Quantity: %d\n", product.quantity);
    printf("Price: %.2f\n", product.price);

    return 0;
}