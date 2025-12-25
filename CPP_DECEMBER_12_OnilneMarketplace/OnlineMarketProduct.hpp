
static int customer_id = 0;
static int seller_id = 0;
static int product_id = 0;

enum class Categories{
    Accessories,
    Auto_parts,
    Books,
    Clothes,
    Cosmetic,
    Electronics,
    Entertainment,
    Household_items,
    Jewelry,
    Meal,
    Medicines,
    Optics,
    Perfume,
    Self_care,
    Watch,
    //watch
    Men_watches,
    Women_watches,
    //Self_care
    Man_Deodorant,
    Woman_Deodorant,
    Shampoo,
    Tweezers,
    Razor,
    //Perfume
    Man_Perfume,
    Woman_Perfume,
    //Optics
    Glasses,
    Lenses,
    Frames,
    //Medicines
    Pills,
    Syrups,
    Powders,
    //Meal
    Candies,
    Chips,
    Culinary_product,
    Fruits,
    Vegetables,
    // Jewelry
    Rings,
    Necklace,
    Earrings,
    // Household_items
    Washing_machine,
    Fridge,
    Vacuum_cleaner,
    Set_of_forks_and_spoons,
    Mugs,
    //Entertainment
    Firecrackers,
    Toys,
    // Electronics
    Phones,
    Laptop,
    TV,
    Speaker,
    // Cosmetic
    Lipstick,
    Mascara,
    Pencil,
    // Clothes
    Man_tops,
    Woman_tops,
    Kids_tops,
    Man_pants,
    Woman_pants,
    Kids_pants,
    Man_bags,
    Woman_bags,
    Kids_bags,
    Man_shoes,
    Woman_shoes,
    Kids_shoes,
    // Books
    Plot_points,
    Comics,
    // Auto_parts
    Spare_parts,
    Consumables,
    // Accessories
    Phone_cases,
    Laptop_cases,
    Phone_Chargers,
    Laptop_Chargers,
    Phone_Coasters,
    Laptop_Coasters
};

enum class Status{
    Assembling,
    On_the_way,
    Delivered
};

enum class Country{
    Russia,
    Armenia,
    France,
    Italy,
    Spain,
    Georgia
};

enum class Role{
    Customer,
    Seller
};