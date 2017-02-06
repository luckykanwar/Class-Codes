<h1>Register</h1>
<p>Please fill out the form below to create an account</p>
<!--Display Errors-->
<?php echo validation_errors('<p class="alert alert-dismissable alert-danger">'); ?>
<?php echo form_open('users/register'); ?>

<!--Field: Username-->
<p>
<?php echo form_label('Username:'); ?>
<?php
$data = array(
              'name'        => 'username',
              'value'       => set_value('username')
            );
?>
<?php echo form_input($data); ?>
</p>

<!--Field: Password-->
<p>
<?php echo form_label('Password:'); ?>
<?php
$data = array(
              'name'        => 'password',
              'value'       => set_value('password')
            );
?>
<?php echo form_password($data); ?>
</p>

<!--Field: Password2-->
<p>
<?php echo form_label('Confirm Password:'); ?>
<?php
$data = array(
              'name'        => 'password2',
              'value'       => set_value('password2')
            );
?>
<?php echo form_password($data); ?>
</p>

<!--Field: Address-->
<p>
<?php echo form_label('Address:'); ?>
<?php
$data = array(
              'name'        => 'address',
              'value'       => set_value('address')
            );
?>
<?php echo form_input($data); ?>
</p>

<!--Field: Phone-->
<p>
<?php echo form_label('Phone:'); ?>
<?php
$data = array(
              'name'        => 'phone',
              'value'       => set_value('phone')
            );
?>
<?php echo form_input($data); ?>
</p>
<!--Field: Email Address-->
<p>
<?php echo form_label('Email Address:'); ?>
<?php
$data = array(
              'name'        => 'email',
              'value'       => set_value('email')
            );
?>
<?php echo form_input($data); ?>
</p>
<!--Submit Buttons-->
<?php $data = array("value" => "Register",
                    "name" => "submit",
                    "class" => "btn btn-primary"); ?>
<p>
    <?php echo form_submit($data); ?>
</p>
<?php echo form_close(); ?>