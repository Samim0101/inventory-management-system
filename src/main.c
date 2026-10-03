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

  product.product_id = 101;
  strcpy(product.product_name, "Keyboard");
  product.quantity = 25;
  product.price = 799.50;

  printf("----- Product Details -----\n");

  printf("Product ID: %d\n", product.product_id);
  printf("Product NAME: %s\n", product.product_name);
  printf("Quantity: %d\n", product.quantity);
  printf("Price: %.2f\n", product.price);

  return 0;
}