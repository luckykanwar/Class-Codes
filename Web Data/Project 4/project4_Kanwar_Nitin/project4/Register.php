<!DOCTYPE html>
<html>
	<head>
		<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
		<link rel="stylesheet" href="style.css">
		<link rel="stylesheet" type="text/css" href="style.css">
		<script type="text/javascript" src="Javascript.js"></script>
	<title>Register </title>
	<header class="header-user-dropdown">
		<div class="header-limiter">
		<h1><a href="#">Cheap<span>Books</span></a></h1>
		</div>
		</header>
		<br/><br/>
	</head>

	<body>
		<div class="container">
			<div class="row">
				<div class="col-md-12">
					<form action="Register.php" method="GET" class="login-block" style="color: black;">
						<h1>Register Here</h1>
						<input type="text" value="" placeholder="Username" id="usernames" name="usr" />
    					<input type="password" value="" placeholder="Password" id="passwords" name="pswd" />
    					<input type="text" name="email" placeholder="Email" id="email"/>
    					<input type="text" name="address" placeholder="Address" id="address" />
    					<input type="tel" name="phone" placeholder="Phone" id="phone"/>
    					<button type="submit" value="submit">Create Account</button>
    					<br/><br/>
  					</form>
  				</div>
  			</div>
  		</div>
  		<?php
			$usrname = $_GET["usr"];
			$pwd = md5($_GET["pswd"]);
			$email = $_GET["email"];
			$addre = $_GET["address"];
			$phone = $_GET["phone"];
			$servername = "localhost";
			$username = "root";
			$password = "backontrack";
			$dbname = "cheapbook";

			$conn = new mysqli($servername, $username, $password, $dbname);
			//mysqli_set_charset($conn,'utf-8');
			// Check connection

			$sql = "select count(1) as cnt from customers where username = '".$usrname."';";
			$result = $conn->query($sql);
			$row = $result->fetch_assoc();
			if(($row["cnt"]==0) && !empty($usrname)) {
				if ($conn->connect_error) {
				die("Connection failed: " . $conn->connect_error);
				}
				$sql = "INSERT INTO customers(UserName,Address,Email,Phone,Password) VALUES ('".$usrname."','".$addre."','".$email."','".$phone."','".$pwd."')";
				//echo $sql;	
				if ($conn->query($sql) == TRUE ) {
					echo '<script>alert("New user has been added!")</script>';
	    			//header('Location: Login.php');
	    			echo '<script type="text/javascript">
							           window.location = "Login.php"
							  </script>';
				} 			
				else {
	    		echo "<span style='color:white;'>Error: </span><span style='color:white;'>" . $sql . "</span><br><span style='color:white;'>" . $conn->error."</span>";
				}
			}
			if($row["cnt"]>0){
				echo '<script>alert("Username already taken ! Please select a different username !")</script>';
			}	
			$conn.close();		 	
		?>
  	<br/>
	</body>
</html>