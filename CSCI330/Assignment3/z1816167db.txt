# Robi Korneta
# Z1816167

#!/bin/bash

numOfCommands=$# # Variable to hold number of commands
dbname=$1        # Variable to hold the first parameter representing the database
command=$2       # Variable to hold the command
param1=$3        # Variable to hold the first parameter
param2=$4        # Variable to hold the second parameter
param3=$5        # Variable to hold the third parameter
param4=$6        # Variable to hold the fourth parameter

# new is a function to create a new database file
#
# It will check to see if the database file already exists
# If the file does not exist, then it will create a new file
#

new () {
   
   if [ -f "$dbname" ]; then             # Check for file existence
      echo "$dbname already exists"
   elif [ $numOfCommands -eq 2 ]; then   # Check to see if header was inputted
     echo "Untitled database" > $dbname
   elif [ $numOfCommands -eq 3 ]; then   # Header was inputted
      echo "$param1" > $dbname
   else
      echo "Not enough parameters"
fi
}

# add will add a database entry into the database file
#
# It will make sure that there are sufficient permissions
# If this is true, then it will create the database entry
# It will also check for missing parameters

add () {

   # Check for file permissions
   if [[ ! -r "$dbname" || ! -w "$dbname" ]]; then
      echo "Insuffiecent Permissions to access $dbname"
      exit
   # Check for missing parameters
   elif [[ $param1 = "" || $param2 = "" || $param4 = "" || $param3 -lt 1870 || $param3 -gt 2025 || $numOfCommands -ne 6 ]]; then
      echo "One or more parameters is invalid"
      exit
   # Insert entry into database file
   else
      echo "$param1, $param2, $param3, $param4" >> $dbname
      echo "Successfully added a recored to the database"
fi
}

# show the database file
#
# Check to make sure that the user has sufficient permissions
# Check to make sure there are database entries
# If both of these are true, then display the file

show () {
   
   lineFix=$(($param2+1))       # Adjusting the line number to account for header
   lineFix1=$(($param3+1))      # Same as above
   count=$(sed -n '$=' $dbname) # Getting count of entries

   # If the count of entries is less than 2 (Must account for header)
   if [ $count -lt 2 ]; then
      
      echo "No Records Found"

   # If file permissions are insufficient
   elif [[ ! -r "$dbname" || ! -w "$dbname" ]]; then

      echo "You do not have sufficient permissions to read this file"

   # Print out the contents of the file
   else

      case "$param1" in
      
         all)
            cat $dbname;;
         single)
            sed -n "$lineFix p" $dbname;;
         range)
            sed -n "$lineFix, $lineFix1 p" $dbname;;
         *)
            echo "Invalid Parameters";;
      esac

fi
}

# delete will delete the specified files in the database file
#
# Check for permissions
# If permissions are suffifiecnt then delete the specified entries

delete () {
   
   lineFix=$(($param2+1))  # Adjusting lines to account for header
   lineFix1=$(($param3+1)) # Same as above
   
   # Check for file permissions
   if [[ ! -r "$dbname" || ! -w "$dbname" || $lineFix -lt 1 ]]; then

      echo "Error in file permissions or parameters. Are you sure the file exists and you have permission to read and write to it?"
    
   # Delete specified entries
   else
      
      case "$param1" in
         
         all)
            sed -i '1!d' $dbname
            echo "All records deleted";;
         single)
            sed -i "$lineFix d" $dbname
            echo "1 record deleted";;
         range)
            sed -i "$lineFix, $lineFix1 d" $dbname
            echo "Records in range deleted";;
         *)
            echo "Error in parameters";;
         
      esac

fi
}

# count will get the total amount of entries in the database file
#
# Check for permissions
# If permissions are sufficient, then display the number of entries

count () {

   # Check for permissions
   if [[ ! -r "$dbname" || ! -w "$dbname" || $numOfCommands -lt 2 ]]; then

      echo "Error in file permissions or parameters. Are you sure the file exists and you have permission to read and write to it?"

   # Get and display the amount of entries
   # Remember to account for header, as it is not an entry
   else
      count1=$(sed -n '$=' $dbname)
      count1=$((count1-1))
      echo "$count1"

fi

}

# This is the main program to run
#
# First, check to make sure that the user inputted a command
# If the user inputted a command, then it will take them to the
# appropriate function to execute

if [ $numOfCommands -eq 0 ]; then
   echo '# dbname  - filename of database file to use'
   echo '# command - which of the functions to call: "new", "add", "show", "delete"'
   echo '# param1  - first non-dbname parameter to whichever command function chosen'
   echo '# ...     - placeholder for parameters between 1 and N'
   echo '# paramN  - Nth parameter for whichever command function chosen'
   stop="n"

else
      case "$command" in

         new)
            new;;
         add)
            add;;
         show)
            show;;
         delete)
            delete;;
         count)
            count;;
         *)
            echo "Invalid Command";;
       esac
fi
