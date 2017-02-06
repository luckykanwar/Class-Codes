<!DOCTYPE html>
<html>
<head>
	<title>
		<?php 
			session_start(); 
			echo "Account: ".$_SESSION["user"];
		?>
	</title>
	<meta charset="utf-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
	<link rel="stylesheet" href="style.css">
</head>
<body>
	<header class="header-user-dropdown">
		<div class="header-limiter">
			<h1><a href="#">Cheap<span>Books</span></a></h1>
			<div class="header-user-menu">
			<div class="text"><?php echo $_SESSION["user"] ?></div>
				<img src="image/carting.jpg" alt="User Image"/>
				<ul>
					<li><div class="text" ><?php echo $_SESSION["user"] ?></div></li>
					<li><a href="ShoppingCart.php?user=<?php echo $_SESSION["user"] ?>"><span class="glyphicon glyphicon-shopping-cart"></span>Shopping Basket</a></li>
					<li><a href="Login.php?logout=logout" class="highlight">Logout</a></li>
				</ul>
			</div>
		</div>
	</header>
	<br/><br/><br/>
	<div class="container">
		<div class="row">
			<div class="col-lg-1"></div>
			<div class="col-lg-10">
				<form action="Account.php" method="GET">  
				  <div class="form-group">
					<div class="Label">	
					    <label for="Textarea">What do you want to Search?</label>
					</div>
				  	<br/>
				  	<textarea class="form-control" id="exampleTextarea" rows="3" name="searchkey"></textarea>
				  	<input type="text" value="logged" id="logged" name="logged" style="display:none"/>
				  </div>
				  <button id="author" class="btn btn-primary" type="submit" name="action" value="authors" >Search By Author</button>
				  <button id="booktitle" class="btn btn-primary" type="submit" name="action" value="titles" >Search By BookTitle</button>
				  <button id="basket" class="btn btn-primary" type="submit" name="action" value="shopping"><span class="glyphicon glyphicon-shopping-cart"></span> Items in Shopping Basket :  
				  		<?php 
				  			//echo "\"".$_SESSION["user"]."\"";
				  			$servername = "localhost";
						    $username = "root";
						    $password = "backontrack";
						    $database = "cheapbook";
						    $conn = new mysqli($servername, $username, $password, $database);	
						    $sql = "select sum(number) as totalItems from contains a inner join shoppingbasket b on a.basketid = b.basketid where a.basketid = (select max(basketid) from shoppingbasket where username = '".$_SESSION["user"]."');";	
							$result = $conn->query($sql);
							$row = $result->fetch_assoc();
							echo $row["totalItems"];
				  		?>
				  	</a></button>
				</form>
			</div>
			<div class="col-lg-1"></div>
		</div>
	</div>
	<div class="container-fluid">
	    <div class="jumbotron changeJumboBackground" style="overflow: auto;">
	    	<?php
	    		$search_value = $_GET["searchkey"];
				$search_criteria = $_GET["action"];
				$logout = $_GET["logout"];


				$red_search_value = $_GET["red_search_value"];
				$red_search_criteria = $_GET["red_search_criteria"];
				$warehousecode = $_GET["warehousecode"];
				$redirectTrue = $_GET["redirectTrue"];

				$logged = $_GET["logged"];
				$id = $_GET["id"];
			    $servername = "localhost";
			    $username = "root";
			    $password = "backontrack";
			    $database = "cheapbook";
			    $arrayMainList = array();
			    $arrayList = array();
		
				//variables for updating the shopping cart
				$title = $_GET["title"];
				$isbn = $_GET["isbn"];
				$numBooks = $_GET["numBooks"];
				$quantity = $_GET["quantity"];
				$update = $_GET["update"];
				$_SESSION["search_value"]=$search_value;
				$_SESSION["search_criteria"]=$search_criteria;

				//echo $_SESSION["search_value"];
				//echo $_SESSION["search_criteria"];
				
				$conn = new mysqli($servername, $username, $password, $database);

				if($logout == 'logout'){
					$sql = "delete from contains;";
					$conn->query($sql);
					session_destroy();
					header("location: Login.php"); 
				}


				if($logged!='logged')
				{
					//echo 'Initially not logged into shoppingbasket';
					if ($conn->connect_error) {
						die("Connection failed: " . $conn->connect_error);
					}
					$sql = "INSERT INTO shoppingbasket(username) VALUES ('".$_SESSION["user"]."')";	
					$conn->query($sql);
				}

				/*if($logged=='logged' && $update!='update')
			    {
					$sql = "select max(basketid) as basketid from shoppingbasket where username =".$_SESSION["user"]."";			
					$result = $conn->query($sql);
					if($result->num_rows > 0)
					{
						$row = $result->fetch_assoc();
						$basketid = $row["basketid"]; 
						echo $basketid; 					
					}					
			    }*/

				if($update=='update' && $logged=='logged'){
					//echo 'Inside update';					
					if ($conn->connect_error) {
						die("Connection failed: " . $conn->connect_error);
					}

					$sql = "select max(basketid) as basketid from shoppingbasket where username ='".$_SESSION["user"]."';";			
					//echo $sql;
					$result = $conn->query($sql);
					$row = $result->fetch_assoc();
					$basketid = $row["basketid"];
					//echo $basketid;
					if(($quantity>$numBooks) || (($numBooks - $quantity))<0){
						echo '<script>alert("Please enter a valid quantity of books!")</script>';
					}
					else{
						$sql = "select count(1) as cnt from contains where basketid =".$basketid." and isbn = '".$isbn."';";
						//echo $sql;
						$result = $conn->query($sql);
						$row = $result->fetch_assoc();
						if ($row["cnt"] > 0){
							$sql="update contains set number = number + " .$quantity. " where basketid =".$basketid." and isbn = '".$isbn."';";
							//echo $sql;
							$conn->query($sql);						
						}
						else
						{
							$sql = "insert into contains(isbn, basketid, number, warehousecode) values('".$isbn."','".$basketid."','".$quantity."','".$warehousecode."');";	
							//echo $sql;
							$conn->query($sql);							
						}
						
						$newNumberOfBooks = $numBooks - $quantity;
						$sql = "update stocks set number = ".$newNumberOfBooks." where isbn = '".$isbn."' and warehousecode = '".$warehousecode."'";
						//echo $sql;
						$conn->query($sql);	
						echo '<script>alert("Book has been added to cart !")</script>';
					}					
					echo '<script>
							window.location="Account.php?redirectTrue=1&searchkey='.$red_search_value.'&logged=logged&action='.$red_search_criteria.'"
						  </script>';
				}

			    if(empty($search_value) && $logged == 'logged' && $update != 'update' && $search_criteria!='shopping' && $redirectTrue != 1)
				{
					//echo 'value is not set';
					$notSet = 1;
					echo '<script>alert("Please enter a valid search value !")</script>';
				}
				if(!empty($search_value) && $logged == 'logged')
				{
					//echo 'value is set';	
					$set = 1;
				}	
			    
				//echo 'The value of set is '.$set;
			    if($search_criteria == "authors" && $set==1){
			    	$sql = "select a.isbn, a.title, a.year, a.price, a.publisher, c.name,sum(d.number) as numBooks, e.name, e.warehousecode from book a inner join writtenby b on a.isbn = b.isbn inner join author c on c.ssn = b.ssn inner join stocks d on d.isbn=a.isbn inner join warehouse e on e.warehousecode = d.warehousecode where c.name like '%" .$search_value. "%' group by a.title, a.isbn, a.year, a.price, a.publisher, c.name, e.warehousecode,e.name having sum(d.number)>0";

				    //echo $sql;
				    $result = $conn->query($sql);

				    if ($result->num_rows > 0) {
		              // output data of each row
				    	echo '<div class="col-lg-1"></div>';
				    	echo '<div class ="col-lg-11">';	               
				    	echo '<div class="div-table" style="font-weight:bold">
				    			<div class="div-row">
				    				<div class="div-table-col">Title</div>
				    				<div class="div-table-col">ISBN</div>
				    				<div class="div-table-col">In Stock</div>
				    				<div class="div-table-col">Location</div>
				    				<div class="div-table-col">Cost of book</div>
				    				<div class="div-table-col">Enter Quantity</div>
				    				<div class="div-table-col">Add to Cart</div>
				    			</div>
				    		  </div>';
		                while($row = $result->fetch_assoc()) {
		                	echo '
		                				<form action = "Account.php" method="GET">
			                			<div class="div-table">
			                				<div class="div-row">
			                					<div class="div-table-col"><span><input type="hidden" name="title" value="'.$row["title"].'">'.$row["title"].'</input></span></div>
			                					<div class="div-table-col"><span><input type="hidden" name="isbn" value="'.$row["isbn"].'">'.$row["isbn"].'</input></span></div>
			                					<div class="div-table-col"><span><input type="hidden" name="numBooks" value="'.$row["numBooks"].'">'.$row["numBooks"].'</input></span></div>
			                					<div class="div-table-col"><span><input type="hidden" name="warehouse" value="'.$row["name"].'">'.$row["name"].'</input></span></div>
			                					<div class="div-table-col"><span><input type="hidden" name="price" value="'.$row["price"].'">'.$row["price"].'</input></span></div>
			                					<div class="div-table-col"><span><input type="text" value="" placeholder="Enter quantity" id="quantity" name="quantity" /></div>
			                					<input type="text" value="update" id="update" name="update" style="display:none"/>
			                					<input type="text" value="'.$row["warehousecode"].'" id="warehousecode" name="warehousecode" style="display:none"/>
			                					<input type="text" value="'.$search_criteria.'" id="red_search_criteria" name="red_search_criteria" style="display:none"/>
			                					<input type="text" value="'.$search_value.'" id="red_search_value" name="red_search_value" style="display:none"/>
			                					<!--<input type="text" value="'.$basketid.'"" id="basketid" name="basketid" style="display:none"/>-->
			                					<input type="text" value="logged" id="logged" name="logged" style="display:none"/>
			                					<div class="div-table-col"><button type="submit" value="Add to Cart">Add to Cart</button></div>
			                				</div>
			                			</div>		
			                			</form>			                		
		                		
				                  ';
		              	}
		                echo '
		                		</div>
		                		<!--<div class="row col-lg-1"></div>-->';
		          	}	
		          	else{
		          		echo '<script>alert("Sorry! We are out of stock for this author!")</script>';
		          	}
			    }	

			    if($search_criteria == "titles" && $set==1){

			    	$sql = "select a.isbn, a.title, a.year, a.price, a.publisher, c.name,sum(d.number) as numBooks, e.name, e.warehousecode from book a inner join writtenby b on a.isbn = b.isbn inner join author c on c.ssn = b.ssn inner join stocks d on d.isbn=a.isbn inner join warehouse e on e.warehousecode = d.warehousecode where a.title like '%" .$search_value. "%' group by a.title, a.isbn, a.year, a.price, a.publisher, c.name, e.warehousecode,e.name having sum(d.number)>0";

				    //echo $sql;
				    $result = $conn->query($sql);

				    if ($result->num_rows > 0) {
		              // output data of each row
				    	echo '<div class="col-lg-1"></div>';
				    	echo '<div class ="col-lg-11">';	               
				    	echo '<div class="div-table" style="font-weight:bold">
				    			<div class="div-row">
				    				<div class="div-table-col">Title</div>
				    				<div class="div-table-col">ISBN</div>
				    				<div class="div-table-col">In Stock</div>
				    				<div class="div-table-col">Location</div>
				    				<div class="div-table-col">Cost of book</div>
				    				<div class="div-table-col">Enter Quantity</div>
				    				<div class="div-table-col">Add to Cart</div>
				    			</div>
				    		  </div>';
		                while($row = $result->fetch_assoc()) {
		                	echo '
		                				<form action = "Account.php" method="GET">
			                			<div class="div-table">
			                				<div class="div-row">
			                					<div class="div-table-col"><span><input type="hidden" name="title" value="'.$row["title"].'">'.$row["title"].'</input></span></div>
			                					<div class="div-table-col"><span><input type="hidden" name="isbn" value="'.$row["isbn"].'">'.$row["isbn"].'</input></span></div>
			                					<div class="div-table-col"><span><input type="hidden" name="numBooks" value="'.$row["numBooks"].'">'.$row["numBooks"].'</input></span></div>
			                					<div class="div-table-col"><span><input type="hidden" name="warehouse" value="'.$row["name"].'">'.$row["name"].'</input></span></div>
			                					<div class="div-table-col"><span><input type="hidden" name="price" value="'.$row["price"].'">'.$row["price"].'</input></span></div>
			                					<div class="div-table-col"><span><input type="text" value="" placeholder="Enter quantity" id="quantity" name="quantity" /></div>
			                					<input type="text" value="update" id="update" name="update" style="display:none"/>
			                					<input type="text" value="'.$row["warehousecode"].'" id="warehousecode" name="warehousecode" style="display:none"/>
			                					<input type="text" value="'.$search_criteria.'" id="red_search_criteria" name="red_search_criteria" style="display:none"/>
			                					<input type="text" value="'.$search_value.'" id="red_search_value" name="red_search_value" style="display:none"/>
			                					<!--<input type="text" value="'.$basketid.'"" id="basketid" name="basketid" style="display:none"/>-->
			                					<input type="text" value="logged" id="logged" name="logged" style="display:none"/>
			                					<div class="div-table-col"><button type="submit" value="Add to Cart">Add to Cart</button></div>
			                				</div>
			                			</div>		
			                			</form>				                		
		                		
				                  ';
		              	}
		                echo '
		                		</div>
		                		<!--<div class="row col-lg-1"></div>-->';
		          	}	
		          	else{
		          		echo '<script>alert("Sorry! We are out of stock for this title!")</script>';
		          	}	
			    }

			    if($search_criteria == "shopping"){
			    	echo '<script type="text/javascript">
							           window.location = "ShoppingCart.php?user='.$_SESSION["user"].'"
						  </script>';
			    }

			    $conn.close();
	    	?>
	    </div>
	</div>
</body>
</html>