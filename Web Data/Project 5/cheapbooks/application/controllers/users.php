<?php
	class Users extends CI_Controller{
		public function register(){
			$this->form_validation->set_rules('username','Username','trim|required|max_length[30]|min_length[4]|xss_clean');
			$this->form_validation->set_rules('password','Password','trim|required|max_length[30]|min_length[4]|xss_clean');
			$this->form_validation->set_rules('password2','Confirm Password','trim|required|max_length[20]|min_length[4]|xss_clean|matches[password]');
			$this->form_validation->set_rules('address','Address','trim|required|max_length[150]|min_length[5]|xss_clean');
			$this->form_validation->set_rules('phone','Phone','trim|required|max_length[15]|min_length[10]|xss_clean');
			$this->form_validation->set_rules('email','Email','trim|required|max_length[100]|min_length[5]|xss_clean|valid_email');
			
			if($this->form_validation->run() == FALSE){
				$this->load->view('layouts/header');
				$this->load->view('users/register');
				$this->load->view('layouts/footer');
			}
			else{
				if($this->User_model->create_member()){
					$this->session->set_flashdata('registered','You are now registered and can login !');
					redirect('home/index');
				}
			}
		}

		public function login(){
			$this->form_validation->set_rules('username','Username','trim|required|max_length[20]|min_length[4]|xss_clean');
			$this->form_validation->set_rules('password','Password','trim|required|max_length[20]|min_length[4]|xss_clean');
			
			if($this->form_validation->run() == FALSE){
				//Do nothing
			}
			else{
				$username = $this->input->post('username');
				$password = $this->input->post('password');

				$data['result'] = $this->User_model->login_user($username, $password);
				foreach($data['result'] as $result){
					$logged_user = $result->username;
					$basketid = $result->basketid;
				}

				if($logged_user == $username){
						$user_data = array(
									'username'  => $logged_user,
									'basketid'  => $basketid,
									'logged_in' => true,
									'bookCount' => 0
									 );					
					$this->session->set_userdata($user_data);
					$this->session->set_flashdata('login_success','You are now logged in !');
					redirect('search');
				}
				else{
					$this->session->set_flashdata('login_falied','Sorry, the login information you entered is incorrect!');
					redirect('home/index');
				}
			}
		}

		public function logout(){
        //Unset user data
	        $this->User_model->logout_user();
	        $this->session->unset_userdata('logged_in');
	        $this->session->unset_userdata('username');
	        $this->session->set_flashdata('logged_out', 'You have been logged out');
	        $this->session->sess_destroy();
		    redirect('home/index');
    	}
	}
?>