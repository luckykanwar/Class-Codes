<?php
	class Search extends CI_Controller{
		public function __construct() {
	        parent::__construct();
	        if(!$this->session->userdata('logged_in')){
	            //Set error
	            $this->session->set_flashdata('need_login', 'Sorry, you need to be logged in to view that area');
	            redirect('home/index');
	        }
    	}

		public function index(){
			$this->load->view('layouts/headerMainPage');
			$this->load->view('search/searchresult');
			$this->load->view('layouts/footer');
		}

		public function getResultAgain(){
			if($this->session->userdata('criteria')=='author'){
				$data['result'] = $this->Search_model->getSearchByAuthor($this->session->userdata('searchkey'));
				if(count($data['result']) > 0){
					$this->session->set_flashdata('search_author_success','Books are available for this author!');
					$this->load->view('layouts/headerMainPage');
					$this->load->view('search/searchresult');
					$this->load->view('search/author',$data);
					$this->load->view('layouts/footer');
				}
				else{
					$this->session->set_flashdata('search_author_failed','Sorry, the author you searched is not available!');
					redirect('search');
				}
				
			}

			if($this->session->userdata('criteria')=='title'){
				$data['result'] = $this->Search_model->getSearchByTitle($this->session->userdata('searchkey'));
				if(count($data['result']) > 0){
					$this->session->set_flashdata('search_title_success','Books are available for this title!');
					$this->load->view('layouts/headerMainPage');
					$this->load->view('search/searchresult');
					$this->load->view('search/title',$data);
					$this->load->view('layouts/footer');
				}
				else{
					$this->session->set_flashdata('search_title_failed','Sorry, the title you searched is not available!');
					redirect('search');
				}
			}
		}

		public function getResult(){
			$criteria = $this->input->post('submit');
			$searchkey = $this->input->post('search_value');

			$data = array(
						'criteria'  => $criteria,
						'searchkey' => $searchkey
						);
			$this->session->set_userdata($data);

			if($criteria=='author'){
				if($searchkey == ''){
					$this->session->set_flashdata('invalid_author','Please enter a valid search value !');
					redirect('search');
				}
				else{

					$data['result'] = $this->Search_model->getSearchByAuthor($searchkey);
					if(count($data['result']) > 0){
						$this->session->set_flashdata('search_author_success','Books are available for this author!');
						$this->load->view('layouts/headerMainPage');
						$this->load->view('search/searchresult');
						$this->load->view('search/author',$data);
						$this->load->view('layouts/footer');
					}
					else{
						$this->session->set_flashdata('search_author_failed','Sorry, the author you searched is not available!');
						redirect('search');
					}
				}
			}

			if($criteria=='title'){
				if($searchkey == ''){
					$this->session->set_flashdata('invalid_title','Please enter a valid search value !');
					redirect('search');
				}
				else{
					$data['result'] = $this->Search_model->getSearchByTitle($searchkey);
					if(count($data['result']) > 0){
						$this->session->set_flashdata('search_title_success','Books are available for this title!');
						$this->load->view('layouts/headerMainPage');
						$this->load->view('search/searchresult');
						$this->load->view('search/title',$data);
						$this->load->view('layouts/footer');
					}
					else{
						$this->session->set_flashdata('search_title_failed','Sorry, the title you searched is not available!');
						redirect('search');
					}
				}	
			}
		}

		public function addtocart(){
			if($this->input->post('quantity') > $this->input->post('numBooks'))
			{
				$this->session->set_flashdata('incorrect_quantity','Please enter a quantity less than or equal to stock !');
				redirect('search/getResultAgain');					
			}
			if($this->Search_model->insertBooksToCart()){
					$this->session->set_flashdata('inserted_to_cart','Book has been inserted to your cart');
					$bookCount = $this->Search_model->getCartCount();
					$this->session->set_userdata('bookCount', $bookCount);
					redirect('search/getResultAgain');
				}
		}
	}
?>