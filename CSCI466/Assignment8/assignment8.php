<!-- Robbie Korneta Z1816167 --- CSCI 466 - 1 --- Assignment 8 --- Due on 11/06/20 at 11:59 PM -->
<html>
<head>
<title>Part Form</title>
<body>
<?php
    
    //View website at http://students.cs.niu.edu/~z1816167/assignment8.php
    
    $username='SomeUsername';
    $password='SomePassword';
    
    /*
     *  Generates a table to display to the user
     *
     *  @param rows -> The rows of data to create that table
     */
    function draw_table($rows) {
        
        echo "<table border=1 cellspacing=1>"; //Set up border and spacing
        echo "<tr>"; //Begin the table row insertion for header row
        
        foreach($rows[0] as $key => $item) {
            
            echo "<th>$key</th>";
            
        }
        
        echo "</tr>";
        
        // Insert data into each row
        foreach ($rows as $row) {
            
            echo "<tr>";
            
            foreach ($row as $key => $item) {
                
                echo "<td>$item</td>"; //Table data
                
            }
            
            echo "</tr>";
            
        }
        
        echo "</table>";
        
    }
    
    /*
     *  Generates a list of the parts that a user can select from
     *
     *  @param parts -> The parts to create a list of
     */
    function listParts($parts) {
        
        echo "<input list=parts name=part>";
        echo "<datalist id=parts>";
        
        // Loop through the parts and insert it as an option
        foreach ($parts as $part) {
            
            echo '<option value="' . $part["PNAME"] . '">'. '</option>';
            
        }
        
        echo "</datalist>";
        
    }
    
    /*
    *  Generates a list of the suppliers that a user can select from
    *
    *  @param suppliers -> The suppliers to create a list of
    */
    function listSuppliers($suppliers) {
        
        echo "<input list=suppliers name=supplier>";
        echo "<datalist id=suppliers>";
        
        // Loop through the suppliers and insert it as an option
        foreach ($suppliers as $supplier) {
            
            echo '<option value="' . $supplier["SNAME"] . ' ">' . '</option>';
            
        }
        
        echo "</datalist>";
        
        
    }
    
    try { // if something goes wrong, an exception is thrown $dsn = "mysql:host=courses;dbname=z123456";
        
        $dsn = "mysql:host=courses;dbname=z1816167"; // Connect to database
        $pdo = new PDO($dsn, $username, $password); // Initiate PDO
        $rs = $pdo->query("SELECT * FROM P;"); // Execute first query to get all parts
        $rows = $rs->fetchAll(PDO::FETCH_ASSOC); // Fetch all the parts from the database
        $srs = $pdo->query("SELECT * FROM S");   // Execute second query to get all suppliers
        $srows = $srs->fetchAll(PDO::FETCH_ASSOC); // Fetch all the suppliers
        $q = "SELECT PNAME FROM P;"; // Get the names of the parts for the list
        $result = $pdo->query($q);   // " " "
        $rows1 = $result->fetchAll(PDO::FETCH_ASSOC); // Fetch all the names
        $sq = "SELECT SNAME FROM S"; // Get supplier names
        $sresult = $pdo->query($sq); // " " "
        $srows1 = $sresult->fetchAll(PDO::FETCH_ASSOC); // Fetch all the supplier names
        
        
        echo "<form method=post action=http://students.cs.niu.edu/~z1816167/assignment8.php>";
        echo "<input type=submit name=showallparts value='Show All Parts'>";
        echo "<input type=submit name=showallsuppliers value='Show All Suppliers'><br><br>";
        
        // Chekc to see if show all parts button was pressed
        if ($_SERVER['REQUEST_METHOD'] == "POST" and isset($_POST['showallparts'])) {
            
            draw_table($rows); // Draw a table of the rows
            echo "<br><br>";
            
        }
        
        // Check to see if show all suppliers button was pressed
        if ($_SERVER['REQUEST_METHOD'] == "POST" and isset($_POST['showallsuppliers'])) {
            
            draw_table($srows); // Draw a table of the rows
            echo "<br><br>";
            
        }
        
        listParts($rows1); // Call to generate the user selected list
        
        echo "<input type=submit name=showparts value='Show Part'/input><br>";
        
        // Check to see if the show parts button was pressed
        if ($_SERVER['REQUEST_METHOD'] == "POST" and isset($_POST['showparts'])) {
            
            $sup = $_POST["part"]; // The part that was selected
            
            $q1 = "SELECT * FROM P WHERE PNAME = ?;"; // Find parts that match
            $query = $pdo->prepare($q1); // Prepare
            $query->execute([$sup]); // Execute query
            
            $row2 = $query->fetch(PDO::FETCH_ASSOC); // Fetch data
            
            echo "Part Number: " .$row2["P"] . " --- Product Name: " . $row2["PNAME"] . " --- Product Color: " . $row2["COLOR"] . " --- Weight: " . $row2["WEIGHT"] . "<br><br>";
            $PID = $row2["P"]; // Get the part primary key
            $q2 = "SELECT * FROM SP WHERE P = ?;"; // Find the part in SP
            $query1 = $pdo->prepare($q2); // Prepare
            $query1->execute([$PID]); // Execute query
            
            $info = $query1->fetchAll(PDO::FETCH_ASSOC); // Fetch all the results from the query
            $storeArray = array(); // Array to hold the stores that have the product
            
            // Check to see if an stores have the product
            if (count($info) > 0) {
                
                // Loop through to get each of the stores from the database
                foreach($info as $s) {
                    
                    $q3 = "Select * FROM S WHERE S = ?;";
                    $query3 = $pdo->prepare($q3);
                    $query3->execute([$s["S"]]);
                    $row3 = $query3->fetch(PDO::FETCH_ASSOC);
                    array_push($storeArray, $row3);
                    
                }
                
                draw_table($storeArray);
                
            } else {
                
                echo "No Suppliers carry this part <br><br>";
                
            }
            
            
        }
        
        listSuppliers($srows1); // List the suppliers for user selection
        
        echo "<input type=submit name=showsuppliers value='Show Supplier'/input><br>";
        
        // Check to see if user clicked on the show suppliers button
        if ($_SERVER['REQUEST_METHOD'] == "POST" and isset($_POST['showsuppliers'])) {
            
            $sup = $_POST["supplier"]; // Get the value that the user selected
            
            // Execute the query
            $q1 = "SELECT * FROM S WHERE SNAME = ?;";
            $query = $pdo->prepare($q1);
            $query->execute([$sup]);
            
            $srow2 = $query->fetch(PDO::FETCH_ASSOC); // Get results of query
            
            echo "Supplier ID: " . $srow2["S"] . " --- Supplier Name: " . $srow2["SNAME"] . " --- Supplier Status: " . $srow2["STATUS"] . " --- Supplier City: " . $srow2["CITY"] . "<br><br>";
            
            $SID = $srow2["S"]; // Get store id
            $q2 = "SELECT * FROM SP WHERE S = ?;"; // Execute another query
            $query1 = $pdo->prepare($q2);          // To get the store info
            $query1->execute([$SID]);
            
            $info = $query1->fetchAll(PDO::FETCH_ASSOC); // Get the results
            $partArray = array(); // Array to hold the parts that the store has
            
            if (count($info) > 0) {
                
                // Loop through and get the product information
                foreach($info as $p) {
                    
                    $q3 = "SELECT * FROM P WHERE P = ?;";
                    $query3 = $pdo->prepare($q3);
                    $query3->execute([$p["P"]]);
                    $row3 = new stdClass();
                    $row3->qty = $p["QTY"];
                    $row3 = $query3->fetch(PDO::FETCH_ASSOC);
                    array_push($partArray, $row3);
                    
                }
                
                draw_table($partArray);
                
            } else {
                
                echo "This Supplier does not carry any parts <br><br>";
                
            }
            
        }
        
        echo "</form>";
        echo "<form method=post action=http://students.cs.niu.edu/~z1816167/assignment8.php>";
        echo "Part Number: <input type=text name=partNumber><br>";
        echo "Part Name:   <input type=text name=partName><br>";
        echo "Color:       <input type=text name=color><br>";
        echo "Weight:      <input type=text name=weight><br>";
        echo "<input type=submit name=addNewPart value='Add New Part'>";
        
        // Checks to see if the user is adding a new part
        if ($_SERVER['REQUEST_METHOD'] == "POST" and isset($_POST['addNewPart'])) {
            
            // Get the info from the posted data
            $partNumber = $_POST["partNumber"];
            $partName = $_POST["partName"];
            $color = $_POST["color"];
            $weight = $_POST["weight"];
            
            // Insert the data into the parts table
            $sql = "INSERT INTO P (P, PNAME, COLOR, WEIGHT) VALUES (:p, :pName, :color, :weight)";
            $write = $pdo->prepare($sql);
            $write->execute(array(':p'=>$partNumber, ':pName'=>$partName, ':color'=>$color, ':weight'=>$weight));
            echo "<br>New Part Created";
            
        }
        
        echo "</form>";
        echo "<form method=post action=http://students.cs.niu.edu/~z1816167/assignment8.php>";
        echo "SupplierID:  <input type=text name=supplyID><br>";
        echo "Supplier Name:   <input type=text name=sName><br>";
        echo "Status:       <input type=text name=status><br>";
        echo "City:      <input type=text name=city><br>";
        echo "<input type=submit name=addNewSupplier value='Add New Supplier'>";
        
        // Check to see if a new supplier is being created
        if ($_SERVER['REQUEST_METHOD'] == "POST" and isset($_POST['addNewSupplier'])) {
            
            // Get the data from the user
            $supplierID = $_POST["supplyID"];
            $sname = $_POST["sName"];
            $status = $_POST["status"];
            $city = $_POST["city"];
            
            // Insert the data into the supplier table
            $sql = "INSERT INTO S (S, SNAME, STATUS, CITY) VALUES (:s, :sName, :status, :city)";
            $write = $pdo->prepare($sql);
            $write->execute(array(':s'=>$supplierID, ':sName'=>$sname, ':status'=>$status, ':city'=>$city));
            echo "<br>New Supplier Created";
            
        }
        
        
        echo "</form>";
        
        
        
    } catch (PDOexception $e) { // handle that exception
        
        echo "Connection to database failed: " . $e->getMessage(); }
    
    ?>

</body>
</head>
</html>
