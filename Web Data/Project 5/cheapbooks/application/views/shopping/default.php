<?php
	if($this->session->flashdata('shipped')){
		echo '<p class="alert alert-dismissable alert-success">';
		echo $this->session->flashdata('shipped');
		echo '</p>';
	}

	else if($this->session->flashdata('no_data_in_cart')){
		echo '<p class="alert alert-dismissable alert-danger">';
		echo $this->session->flashdata('no_data_in_cart');
		echo '</p>';
	}
	
	else{
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
	foreach($result as $result){
		echo '<tr>
				<td>'.$result->isbn.'</td>
				<td>'.$result->title.'</td>
				<td>'.$result->author_name.'</td>
				<td>'.$result->warehousename.'</td>
				<td>'.$result->numberInBasket.'</td>
				<td>'.$result->price.'</td>
			  </tr>';
		$total_cost = $total_cost + $result->price ;
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
		echo '<p>';
		$data = array('name' 		=> 'redirect', 
					  'class' 		=> 'btn btn-primary'
					  );
		echo anchor('shoppingcart/buyShoppingCart','Buy',$data);
		echo '</p>';
	}	
?>
<p>
	<?php
		$data = array('name' 		=> 'redirect', 
					  'class' 		=> 'btn btn-primary'
					  );
		echo anchor('search','Go back and buy more books!',$data);
	?>
	
</p>