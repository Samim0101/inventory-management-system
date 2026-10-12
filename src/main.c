
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <math.h>

typedef struct
{
    int product_id;
    char product_name[50];
    int quantity;
    float price;
} Product;
int rewrite_products(Product products[], int product_count);
int read_int(const char *prompt);
float read_float(const char *prompt);
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

int search_product(Product products[], int product_count, int product_id)
{
    for (int i = 0; i < product_count; i++)
    {
        if (products[i].product_id == product_id)
        {
            printf("=========================\n");
            printf("     PRODUCT FOUND\n");
            printf("=========================\n");

            printf("PRODUCT ID: %d\n", products[i].product_id);
            printf("PRODUCT NAME: %s\n", products[i].product_name);
            printf("PRODUCT QUANTITY: %d\n", products[i].quantity);
            printf("PRODUCT PRICE: %.2f\n", products[i].price);
            return 1;
        }
    }
    printf("Product not found!\n");
    return 0;
}

int delete_product(Product products[], int *product_count, int product_id)
{
    for (int i = 0; i < *product_count; i++)
    {
        if (products[i].product_id == product_id)
        {

            Product deleted = products[i];
            int old_count = *product_count;

            for (int j = i; j < old_count - 1; j++)
            {
                products[j] = products[j + 1];
            }

            (*product_count)--;

            if (rewrite_products(products, *product_count))
            {
                printf("Product deleted successfully!\n");
                return 1;
            }

            for (int j = *product_count; j > i; j--)
            {
                products[j] = products[j - 1];
            }

            products[i] = deleted;
            (*product_count)++;

            printf("Error updating product file!\n");
            printf("The product has been restored in memory.\n");
            return 0;
        }
    }

    printf("Product not found!\n");
    return 0;
}
int update_product(Product products[], int product_count, int product_id)
{
    for (int i = 0; i < product_count; i++)
    {
        if (products[i].product_id == product_id)
        {
            Product updated = products[i];

            printf("\n===== CURRENT PRODUCT DETAILS =====\n");
            printf("Product ID: %d\n", products[i].product_id);
            printf("Product Name: %s\n", products[i].product_name);
            printf("Quantity: %d\n", products[i].quantity);
            printf("Price: %.2f\n", products[i].price);

            printf("\n===== ENTER NEW PRODUCT DETAILS =====\n");

            printf("Enter new product name: ");

            if (fgets(updated.product_name,
                      sizeof(updated.product_name), stdin) == NULL)
            {
                return 0;
            }

            updated.product_name[strcspn(updated.product_name, "\n")] = '\0';

            if (strlen(updated.product_name) == 0)
            {
                printf("Product name cannot be empty!\n");
                return 0;
            }

            updated.quantity = read_int("Enter new quantity: ");

            if (updated.quantity < 0)
            {
                printf("Quantity cannot be negative!\n");
                return 0;
            }

            updated.price = read_float("Enter new price: ");

            if (updated.price < 0)
            {
                printf("Price cannot be negative!\n");
                return 0;
            }

            Product original = products[i];
            products[i] = updated;

            if (rewrite_products(products, product_count))
            {
                printf("\nProduct updated successfully!\n");
                return 1;
            }

            products[i] = original;
            printf("Error updating product file!\n");
            return 0;
        }
    }

    printf("Product not found!\n");
    return 0;
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

int rewrite_products(Product products[], int product_count)
{
    FILE *file = fopen("../data/products.dat", "wb");

    if (file == NULL)
    {
        perror("Error opening product file");
        return 0;
    }

    int success = 1;

    for (int i = 0; i < product_count; i++)
    {
        if (fwrite(&products[i], sizeof(Product), 1, file) != 1)
        {
            success = 0;
            break;
        }
    }

    if (fclose(file) != 0)
    {
        success = 0;
    }

    if (!success)
    {
        printf("Error writing product data!\n");
        return 0;
    }

    return 1;
}

int product_id_exists(Product products[], int product_count, int product_id)
{
    for (int i = 0; i < product_count; i++)
    {
        if (products[i].product_id == product_id)
        {
            return 1;
        }
    }

    return 0;
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
    product.product_id = read_int("Enter product ID: ");

    if (product_id_exists(products, *product_count, product.product_id))
    {
        printf("Error: Product ID already exists!\n");
        return 0;
    }

    printf("Enter product name: ");

    if (fgets(product.product_name,
              sizeof(product.product_name), stdin) == NULL)
    {
        return 0;
    }

    product.product_name[strcspn(product.product_name, "\n")] = '\0';

    if (strlen(product.product_name) == 0)
    {
        printf("Product name cannot be empty!\n");
        return 0;
    }

    product.quantity = read_int("Enter quantity: ");

    if (product.quantity < 0)
    {
        printf("Quantity cannot be negative!\n");
        return 0;
    }

    product.price = read_float("Enter price: ");

    if (product.price < 0)
    {
        printf("Price cannot be negative!\n");
        return 0;
    }

    if (save_product(product))
    {
        products[*product_count] = product;
        (*product_count)++;

        printf("Product added successfully!\n");
        return 1;
    }

    return 0;
}

int load_products(Product products[], int *product_count)
{
    FILE *file = fopen("../data/products.dat", "rb");

    if (file == NULL)
    {
        printf("No saved products found.\n");
        return 0;
    }
    while (*product_count < 100 &&
           fread(&products[*product_count], sizeof(Product), 1, file) == 1)
    {
        (*product_count)++;
    }
    fclose(file);
    printf("Products load successfully!\n");
    return 1;
}

int read_int(const char *prompt)
{
    char input[100];
    char *end;
    long value;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("\nInput closed. Exiting program.\n");
            exit(EXIT_SUCCESS);
        }

        errno = 0;
        value = strtol(input, &end, 10);

        while (*end == ' ' || *end == '\t' ||
               *end == '\n' || *end == '\r')
        {
            end++;
        }

        if (end != input &&
            *end == '\0' &&
            errno != ERANGE &&
            value >= INT_MIN &&
            value <= INT_MAX)
        {
            return (int)value;
        }

        printf("Invalid input! Please enter a whole number.\n");
    }
}

float read_float(const char *prompt)
{
    char input[100];
    char *end;
    float value;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("\nInput closed. Exiting program.\n");
            exit(EXIT_SUCCESS);
        }

        errno = 0;
        value = strtof(input, &end);

        while (*end == ' ' || *end == '\t' ||
               *end == '\n' || *end == '\r')
        {
            end++;
        }

        if (end != input &&
            *end == '\0' &&
            errno != ERANGE &&
            isfinite(value))
        {
            return value;
        }

        printf("Invalid input! Please enter a valid number.\n");
    }
}

int main()
{
    Product products[100];
    int product_count = 0;
    int choice;
    load_products(products, &product_count);
    while (1)
    {
        printf("\n===== INVENTORY MANAGEMENT SYSTEM =====\n");
        printf("1. Add Product\n");
        printf("2. Display Products\n");
        printf("3. Search Product\n");
        printf("4. Delete Product\n");
        printf("5. Update Product\n");
        printf("6. Exit\n");

        choice = read_int("Enter your choice: ");

        switch (choice)
        {
        case 1:
            add_product(products, &product_count);
            break;

        case 2:
            display_product(products, product_count);
            break;

        case 3:
        {
            int product_id;

            product_id = read_int("Enter product ID to search: ");

            search_product(products, product_count, product_id);
            break;
        }

        case 4:
        {
            int product_id;

            product_id = read_int("Enter product ID to delete: ");

            delete_product(products, &product_count, product_id);
            break;
        }

        case 5:
        {
            int product_id;

            product_id = read_int("Enter product ID to update: ");

            update_product(products, product_count, product_id);
            break;
        }

        case 6:
            printf("Exiting program...\n");
            return 0;

        default:
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}