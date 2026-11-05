import random
import pandas as pd
import sqlite3 

user_info = []
user_info_full = []
folderpath = "./data/raw/" 

# COMMENT OUT THIS LINE IF YOU WANT YOUR OWN DATASET. CURRENTLY GIVES THE SAME DATASET OVER AND OVER AGAIN FOR TESTING PURPOSES
random.seed(1)

# creates fake users
for user_id in range(1, 40001):
    # randomizes the device of the user with 40% chance of being desktop and 60% chance of being mobile
    device_roll = random.random()
    if device_roll <= 0.4: 
        device = 'Desktop'
    else:
        device = 'Mobile'

    # randomizes the user type of the user with 70% chance of being new and 30% chance of being returning
    user_type_roll = random.random()
    if user_type_roll <= 0.7:
        user_type = 'New'
    else:
        user_type = 'Returning'

    # randomizes the traffic source of the user with 30% chance of being organic, 30% chance of being paid, and 40% chance of being referral
    traffic_source_roll = random.random()
    if traffic_source_roll <= 0.3:
        traffic_source = 'Organic'
    elif traffic_source_roll <= 0.6:
        traffic_source = 'Paid'
    else:
        traffic_source = 'Referral'

    # randomizes the group of the user
    group = random.choice(['A', 'B'])

    # randomizes the decision of the user to buy or not depending on the group and the device
    purchase_chance = random.random()
    if device == 'Desktop':
        if group == 'A':
            if purchase_chance <= 0.12: # Desktop users in group A with 12% chance of buying
                purchased = 1
                order_price = 49.99 # Placeholder price for now. Can be randomized if needed.
            else: 
                purchased = 0
                order_price = 0
        else:
            if purchase_chance <= 0.123: # Desktop users in group B with 12.3% chance of buying
                purchased = 1
                order_price = 49.99 # Placeholder price for now. Can be randomized if needed.
            else:
                purchased = 0
                order_price = 0
    else:
        if group == 'A':
            if purchase_chance <= 0.09: # Mobile users in group A with 9% chance of buying
                purchased = 1
                order_price = 49.99 # Placeholder price for now. Can be randomized if needed.
            else: 
                purchased = 0
                order_price = 0
        else:
            if purchase_chance <= 0.11: # Mobile users in group B with 11% chance of buying
                purchased = 1
                order_price = 49.99 # Placeholder price for now. Can be randomized if needed.
            else:
                purchased = 0
                order_price = 0

    # Store all the information in a list to be transformed into a pandas dataframe with only the 5 first columns for the current C++ part

    user_info.append([user_id, device, group, purchased, order_price])
    # Store all the information in a list to be transformed into a pandas dataframe           
    user_info_full.append([user_id, device, group, purchased, order_price, user_type, traffic_source])

df_v1 = pd.DataFrame(user_info, columns=['user_id', 'device', 'variant', 'purchased', 'order_price'])
df_v2 = pd.DataFrame(user_info_full, columns=['user_id', 'device', 'variant', 'purchased', 'order_price', 'user_type', 'traffic_source'])
print(df_v2.head())

# group by device and group to get the conversion rate of each set of device and group
grouped_pd = df_v1.groupby(['device', 'variant'], as_index=False)['purchased'].mean().rename(columns={'purchased': 'Conversion Rate'})
print(grouped_pd)

# Save the dataframe to a csv file for C++ part
df_v1.to_csv(folderpath + 'generated_users.csv', index=False)
df_v2.to_csv(folderpath + 'generated_users_full.csv', index=False)

# Save the dataframe to a SQLite database
connection = sqlite3.connect('generated_users.db')
df_v2.to_sql(name='generated_users', con=connection, if_exists='replace', index=False)
connection.close()