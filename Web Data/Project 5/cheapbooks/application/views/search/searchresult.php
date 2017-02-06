<?php 
	if($this->session->flashdata('login_success')){
		echo '<p class="alert alert-dismissable alert-success">';
		echo $this->session->flashdata('login_success');
		echo '</p>';
	}

	/*if($this->session->userdata('logged_in')){
		echo '<p>You are logged in as ';
		echo $this->session->userdata('username');
		echo 'and your basketid is ';
		echo $this->session->userdata('basketid');
		echo '</p>';

		$attributes = array(
							'id' 	=> 'logout_form',
							'class' => 'form-horizontal'
						);
		echo '<p>';
		echo form_open('users/logout',$attributes);
		$data = array("value" => "Logout",
                      "name"  => "submit",
                      "class" => "btn btn-primary");
		echo form_submit($data);
		echo form_close();
		echo '</p>';
	}*/
	if($this->session->flashdata('incorrect_quantity')){
		echo '<p class="alert alert-dismissable alert-danger">';
		echo $this->session->flashdata('incorrect_quantity');
		echo '</p>';
	}
	
	if($this->session->flashdata('invalid_title')){
		echo '<p class="alert alert-dismissable alert-danger">';
		echo $this->session->flashdata('invalid_title');
		echo '</p>';
	}

	if($this->session->flashdata('invalid_author')){
		echo '<p class="alert alert-dismissable alert-danger">';
		echo $this->session->flashdata('invalid_author');
		echo '</p>';
	}

	if($this->session->flashdata('search_author_failed')){
		echo '<p class="alert alert-dismissable alert-danger">';
		echo $this->session->flashdata('search_author_failed');
		echo '</p>';
	}

	if($this->session->flashdata('search_author_success')){
		echo '<p class="alert alert-dismissable alert-success">';
		echo $this->session->flashdata('search_author_success');
		echo '</p>';
	}

	if($this->session->flashdata('search_title_failed')){
		echo '<p class="alert alert-dismissable alert-danger">';
		echo $this->session->flashdata('search_title_failed');
		echo '</p>';
	}

	if($this->session->flashdata('search_title_success')){
		echo '<p class="alert alert-dismissable alert-success">';
		echo $this->session->flashdata('search_title_success');
		echo '</p>';
	}

	$attributes = array('id' => 'login_form', 
						'class' => 'form-horizontal'
					 	);
	echo form_open('search/getResult',$attributes);

	$data = array(
					  'name' 		=> 'search_value', 
					  'placeholder' => 'Enter search value',
					  'style' 		=> 'width:90%',
					  'value' 		=> set_value('search_value')
				);
	echo form_input($data); 
	
	$data = array(
					  'name' 		=> 'submit', 
					  'class' 		=> 'btn btn-primary',
					  'value' 		=> 'author'
				);
	
	echo form_submit($data); 

	$data = array(
					  'name' 		=> 'submit', 
					  'class' 		=> 'btn btn-primary',
					  'value' 		=> 'title'
				);
	
	echo form_submit($data); 

	echo form_close();	
?>
<p>
	<?php
		$data = array('name' 		=> 'redirect', 
					  'class' 		=> 'btn btn-primary'
					  );
		echo anchor('shoppingcart/displayShoppingCart','Shopping Cart (' . $this->session->userdata('bookCount') . ')',$data);
	?>
	
</p>