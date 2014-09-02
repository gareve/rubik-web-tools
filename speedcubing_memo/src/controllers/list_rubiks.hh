<?hh //decl
header('Content-Type: application/json');

$moves = Vector{
	Map {'name' => 'cuack_move123', 'answer' => 'LRDE', 'id' => 3},
	Map {'name' => 'cuack_move123', 'answer' => 'LRDE', 'id' => 4}
};
echo json_encode($moves);