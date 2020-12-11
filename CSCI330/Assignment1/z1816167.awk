
# Robi Korneta
# Z1816167
# Assignment 7

BEGIN {

        FS = ":" #Setting the field seperator to :
        printf("%-10s\t\t%-14s%s\n", "Name", "Position", "Sales Amount") #Print the header
        print("==================================================") #Print the header

}

NF == 3 { #This Represents the Associates Record, as it has 4 fields

        name[$1] = $2 " " $3 #Store the name of the associate and position for later
                             #into the index represented by the Associate ID

}

NF == 4 { #This represents the products Record

        productAmount[$1] = $4 #Store the price of the product at the index of the associate ID

}

/2018/ { #We only want records from 2018, so this will check to make sure the record is from 2018

        saleTotal[$5] += $3 * productAmount[$2] #Adding up the total amount of sales for
                                                #Each Associate

}

END {
        

        for(x in saleTotal) { #Loop through the saletotal array and print

                split(name[x], a, " ") #Split the name into a[1] = First name, a[2] =  last name, 
                                       #a[3] = position
                
                #Print out the resulting array, sorted by the sales total
                printf("%s, %-10s\t%-10s\t%10.2f\n", a[2], a[1], a[3], saleTotal[x]) | "sort -nr -k 4"

        }

}

