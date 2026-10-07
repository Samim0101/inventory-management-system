
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int product_id;
    char product_name[50];
    int quantity;
    float price;
} Product;
int rewrite_products(Product products[], int product_count);
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
            for (int j = i; j < *product_count - 1; j++)
            {
                products[j] = products[j + 1];
            }

            (*product_count)--;

            if (rewrite_products(products, *product_count))
            {
                printf("Product deleted successfully!\n");
                return 1;
            }

            printf("Error updating product file!\n");
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
            printf("\n===== CURRENT PRODUCT DETAILS =====\n");
            printf("Product ID: %d\n", products[i].product_id);
            printf("Product Name: %s\n", products[i].product_name);
            printf("Quantity: %d\n", products[i].quantity);
            printf("Price: %.2f\n", products[i].price);

            printf("\n===== ENTER NEW PRODUCT DETAILS =====\n");

            // Clear the newline left by scanf()
            getchar();

            printf("Enter new product name: ");
            if (fgets(products[i].product_name,
                      sizeof(products[i].product_name), stdin) == NULL)
            {
                return 0;
            }

            // Remove the newline from the product name
            products[i].product_name[strcspn(products[i].product_name, "\n")] = '\0';

            printf("Enter new quantity: ");
            if (scanf("%d", &products[i].quantity) != 1)
            {
                printf("Invalid quantity!\n");
                return 0;
            }

            printf("Enter new price: ");
            if (scanf("%f", &products[i].price) != 1)
            {
                printf("Invalid price!\n");
                return 0;
            }

            // Save updated product details to the file
            if (rewrite_products(products, product_count))
            {
                printf("\nProduct updated successfully!\n");
                return 1;
            }

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
        printf("Error opening file!\n");
        return 0;
    }

    for (int i = 0; i < product_count; i++)
    {
        fwrite(&products[i], sizeof(Product), 1, file);
    }

    fclose(file);
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

    printf("Enter product ID: ");
    if (scanf("%d", &product.product_id) != 1)
    {
        printf("Invalid product ID!\n");
        return 0;
    }

    if (product_id_exists(products, *product_count, product.product_id))
    {
        printf("Error: Product ID already exists!\n");
        return 0;
    }

    getchar();

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

    printf("Enter quantity: ");
    if (scanf("%d", &product.quantity) != 1)
    {
        printf("Invalid quantity! Please enter a number.\n");
        return 0;
    }

    if (product.quantity < 0)
    {
        printf("Quantity cannot be negative!\n");
        return 0;
    }

    printf("Enter price: ");

    if (scanf("%f", &product.price) != 1)
    {
        printf("Invalid price! Please enter a number.\n");
        return 0;
    }

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
    int value;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            return 0;
        }

        if (sscanf(input, "%d", &value) == 1)
        {
            return value;
        }

        printf("Invalid input! Please enter a number.\n");
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

            printf("Enter product ID to search: ");
            scanf("%d", &product_id);

            search_product(products, product_count, product_id);
            break;
        }

        case 4:
        {
            int product_id;

            printf("Enter product ID to delete: ");
            scanf("%d", &product_id);

            delete_product(products, &product_count, product_id);
            break;
        }

        case 5:
        {
            int product_id;

            printf("Enter product ID to update: ");
            scanf("%d", &product_id);

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