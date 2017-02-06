<!DOCTYPE html>
<html>
<head>
	<title></title>
	<!--<link rel="stylesheet" type="text/css" href="<?php echo base_url();?>assets/css/bootstrap.css">-->
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">	
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
</head>
<body>
	<div class="navbar navbar-inverse navbar-fixed-top">
      <div class="navbar-inner">
        <div class="container-fluid">
          <a class="brand" href="#">myTodo</a>
          <div>
            <p>
             <!--RIGHT TOP CONTENT-->
                <a href="<?php echo base_url(); ?>users/register">Register</a>
            </p>
            <ul class="nav">
              <li><a href="<?php echo base_url(); ?>">Home</a></li>
            </ul>
          </div><!--/.nav-collapse -->
        </div>
      </div>
    </div>

    <div class="container-fluid">
      <div class="row-fluid">
        <div class="span3">
          <div class="well sidebar-nav">
          <div style="margin:0 0 10px 10px;">
			<!--SIDEBAR CONTENT-->
			<?php $this->load->view('users/login'); ?>
          </div>
          </div><!--/.well -->
        </div><!--/span-->

        <div class="span9">
   		<!--MAIN CONTENT-->
			<?php $this->load->view($main_content); ?>
        </div><!--/span-->
		</div><!--/row-->
      <hr>

      <footer>
        <p>&copy; Copyright 2013</p>
      </footer>
    </div><!--/.fluid-container-->    
</body>
</html>