<!DOCTYPE html>
<html>
<head>
	<title>Cart of <?php session_start(); echo $_GET["user"]; ?></title>
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
			<div class="text"><?php echo $_GET["user"] ?></div>
				<img src="image/carting.jpg" alt="User Image"/>
				<ul>
					<li><div class="text" ><?php echo $_GET["user"] ?></div></li>
					<li><a href="ShoppingCart.php?user=<?php echo $_GET["user"] ?>"><span class="glyphicon glyphicon-shopping-cart"></span>Shopping Basket</a></li>
					<li><a href="Login.php?logout=logout" class="highlight">Logout</a></li>
				</ul>
			</div>
		</div>
	</header>
	<div class="container-fluid" style="margin-top:100px">
	    <div class="jumbotron changeJumboBackground" style="overflow: auto;">
	    	<?php
	    		$servername = "localhost";
			    $username = "root";
			    $password = "backontrack";
			    $database = "cheapbook";
			    $user = $_GET["user"];
			    $keyword = $_GET["keyword"];
			    $conn = new mysqli($servername, $username, $password, $database);
			    $arrayList = array();
			    $_SESSION["user"] = $_GET["user"];
			    $logout = $_GET["logout"];

			    if($logout == 'logout'){
					$sql = "delete from contains;";
					$conn->query($sql);
					session_destroy();
					header("location: Login.php"); 
				}

			    //previous orders
			    $sql="select b.title,b.isbn,d.name, a.number,e.name as warehousename, a.number*b.price as totalCost from shippingorder a inner join book b on a.isbn=b.isbn inner join writtenby c on c.isbn=b.isbn inner join author d on d.ssn = c.ssn inner join warehouse e on e.warehousecode=a.warehousecode where username = '".$_GET["user"]."';";
			    //echo $sql;			    
			    $result = $conn->query($sql);
			    if ($result->num_rows > 0) {
			    	
			    	echo '<div class="jumbotron changeJumboBackground">';
			    	echo '<div class="row col-lg-1"></div>';
				    	echo '<div class = "col-lg-10" >';	     
				    	echo '<table>
				    			<tr>
				    				<th colspan="6" style="font-weight:bold">Shopping History</th>
				    			</tr>
				    			<tr>
				    				<th>ISBN</th>
				    				<th>Title</th>
				    				<th>Author</th>
				    				<th>Being Shipped From</th>
				    				<th>Number of Items</th>				    				
				    				<th>Price</th>
				    			</tr>
				    		 ';
				    	
					    while($row = $result->fetch_assoc()) {
					    	array_push($arrayList,$row["isbn"],$row["title"],$row["name"],$row["numberInBasket"]);
					    	echo '<tr>
					    			<td>'.$row["isbn"].'</td>
					    			<td>'.$row["title"].'</td>
					    			<td>'.$row["name"].'</td>
					    			<td>'.$row["warehousename"].'</td>
					    			<td>'.$row["number"].'</td>
					    			<td>'.$row["totalCost"].'</td>
					    		  </tr>
					    		 ';
					    	
					    }
					  
						echo '</table>
						</div>
					</div>
			</div>';
		}
			    
			    //new orders
			    $sql = "select f.name, d.title, d.isbn, a.basketid, sum(a.number) numberInBasket, sum(a.number)*d.price as price, a.warehousecode, c.name as warehousename from contains a inner join shoppingbasket b on a.basketid = b.basketid inner join warehouse c on a.warehousecode = c.warehousecode inner join book d on d.isbn = a.isbn inner join writtenby e on e.isbn = d.isbn inner join author f on f.ssn = e.ssn where b.username = '".$_GET["user"]."' group by f.name, d.title,d.isbn,a.basketid,a.warehousecode,c.name;";

				//echo $sql;			    
			    $result = $conn->query($sql);
			    if ($result->num_rows > 0) {
			    	echo '<div class="row col-lg-1"></div>';
				    	echo '<div class = "col-lg-10" >';	     
				    	echo '<table>
				    			<tr>
				    				<th colspan="6" style="font-weight:bold">Current Shopping Cart Status</th>
				    			</tr>
				    			<tr>
				    				<th>ISBN</th>
				    				<th>Title</th>
				    				<th>Author</th>
				    				<th>Being Shipped From</th>
				    				<th>Number of Items</th>				    				
				    				<th>Price</th>
				    			</tr>
				    		 ';
				    	$total_cost = 0;
					    while($row = $result->fetch_assoc()) {
					    	array_push($arrayList,$row["isbn"],$row["title"],$row["name"],$row["numberInBasket"]);
					    	echo '<tr>
					    			<td>'.$row["isbn"].'</td>
					    			<td>'.$row["title"].'</td>
					    			<td>'.$row["name"].'</td>
					    			<td>'.$row["warehousename"].'</td>
					    			<td>'.$row["numberInBasket"].'</td>
					    			<td>'.$row["price"].'</td>
					    		  </tr>
					    		 ';
					    	$total_cost = $total_cost + $row["price"] ;
					    }
					    echo '<tr>
				    				<td></td>
				    				<td></th>
				    				<td></td>
				    				<td></td>
				    				<td style="font-weight:bold;">Total Price</td>				    				
				    				<td>'.$total_cost.'</td>
				    			</tr>';
						echo '</table>
						</div>
					</div>';
					echo '<br/><br/>';
					echo '<div id="buyButton"><a href="ShoppingCart.php?user='.$_GET["user"].'&keyword=buy">Buy</a></div>';
			    }
			    else{
			    		echo '<script>alert("There are no items in your current shopping cart !")</script>';
			    				    }

			    if($keyword=='buy'){
			    	$result = $conn->query($sql);
			    	if ($result->num_rows > 0) {
			    		while($row = $result->fetch_assoc()) {
				    		$sql1 = "insert into shippingorder (isbn,warehousecode,username,number) values('".$row["isbn"]."','".$row["warehousecode"]."','".$user."',".$row["numberInBasket"].");";
				    		//echo $sql1;
				    		$conn->query($sql1);
				    	}
				    	$sql1 = "delete from contains;";
				    	$conn->query($sql1);
				    	echo '<script>alert("Shipping Order has been dispatched and you current cart has been cleared !")</script>';
						echo '<script type="text/javascript">
							           window.location = "ShoppingCart.php?user='.$_GET["user"].'"
						  </script>';
				    	//echo ShoppingCart.php?user=lucky
			    	}
			    }
			    echo '<br/><br/>';
			    echo '<div id="backButton"><a href="Account.php?redirectTrue=1&returnFromShoppingCart=1&logged=logged">Go back to search page and add more items</a></div>';
			    $conn.close();
			    /*
			    echo '<script type="text/javascript">
							           window.location = "Account.php"
						  </script>';*/
	    	?>
	    </div>
	</div>

</body>
</html>
