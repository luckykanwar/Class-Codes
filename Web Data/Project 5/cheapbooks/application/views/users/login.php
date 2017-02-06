<?php 
	$attributes = array('id' => 'login_form', 
						'class' => 'login-block form-horizontal'
					 	);
	echo form_open('users/login',$attributes);
?>
<p>
	<?php 
		echo form_label('Username'); 
		$data = array('name' 		=> 'username', 
					  'placeholder' => 'Enter Username',
					  'style' 		=> 'width:90%',
					  'value' 		=> set_value('username')
					);
		echo form_input($data); 
	?>
</p>
<p>
	<?php 
		echo form_label('Password');

		$data = array('name' 		=> 'password', 
					  'placeholder' => 'Enter Password',
					  'style' 		=> 'width:90%',
					  'value' 		=> set_value('password')
					);
		echo form_password($data); 
	?>
</p>
<p>	
	<?php 
		$data = array('name' 		=> 'submit', 
					  'class' 		=> 'btn btn-primary',
					  'value' 		=> 'Login'
					);
	
		echo form_submit($data); 
	?>
</p>
<?php 
	echo form_close();
?>
<p>
	<?php
		$data = array('name' 		=> 'redirect', 
					'style' => 'margin-left:42%',
					  'class' 		=> 'btn btn-primary'
					  );
		echo anchor('users/register','Create New Account',$data);
	?>
	
</p>
