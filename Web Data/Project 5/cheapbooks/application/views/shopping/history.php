<?php

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
				    				<th>Was Shipped From</th>
				    				<th>Number of Items</th>				    				
				    				<th>Price</th>
				    			</tr>
				    		 ';
		
	foreach($result as $result){
		echo '<tr>
				<td>'.$result->isbn.'</td>
				<td>'.$result->title.'</td>
				<td>'.$result->author_name.'</td>
				<td>'.$result->warehousename.'</td>
				<td>'.$result->numberInBasket.'</td>
				<td>'.$result->price.'</td>
			  </tr>';
	}	
		echo '</table>
			</div>
		</div>';
		
?>