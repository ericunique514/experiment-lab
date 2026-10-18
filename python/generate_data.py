import random
import pandas as pd
import sqlite3 

user_info = []

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

    # randomizes the group of the user
    group = random.choice(['A', 'B'])

    # randomizes the decision of the user to buy or not depending on the group and the device
    purchase_chance = random.random()
    if device == 'Desktop':
        if group == 'A':
            if purchase_chance <= 0.12: # Desktop users in group A with 12% chance of buying
                decision = 1
                order_price = 49.99 # Placeholder price for now. Can be randomized if needed.
            else: 
                decision = 0
                order_price = 0
        else:
            if purchase_chance <= 0.123: # Desktop users in group B with 12.3% chance of buying
                decision = 1
                order_price = 49.99 # Placeholder price for now. Can be randomized if needed.
            else:
                decision = 0
                order_price = 0
    else:
        if group == 'A':
            if purchase_chance <= 0.09: # Mobile users in group A with 9% chance of buying
                decision = 1
                order_price = 49.99 # Placeholder price for now. Can be randomized if needed.
            else: 
                decision = 0
                order_price = 0
        else:
            if purchase_chance <= 0.11: # Mobile users in group B with 11% chance of buying
                decision = 1
                order_price = 49.99 # Placeholder price for now. Can be randomized if needed.
            else:
                decision = 0
                order_price = 0

    # Store all the information in a list to be transformed into a pandas dataframe           
    user_info.append([user_id, device, group, decision, order_price])

df = pd.DataFrame(user_info, columns=['User ID', 'Device', 'Group', 'Decision', 'Order Price'])
print(df)

# Group by device and group to get the conversion rate of each set of device and group
grouped_pd = df.groupby(['Device', 'Group'], as_index=False)['Decision'].mean().rename(columns={'Decision': 'Conversion Rate'})
print(grouped_pd)

# Save the dataframe to a csv file for C++ part
df.to_csv('generated_users.csv')

# Save the dataframe to a SQLite database
connection = sqlite3.connect('generated_users.db')
df.to_sql(name='generated_users', con=connection, if_exists='replace', index=False)
connection.close()