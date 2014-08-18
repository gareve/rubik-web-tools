<?hh // strict
type Matrix<T> = Vector<Vector<T>>;

class RubikTopView{
	public Matrix<bool> $grid;
    public Vector<bool> $hsides;
    public Vector<bool> $vsides;
    public string $answer;
    public string $name;

    public function __construct(Matrix<bool> $grid,Vector<bool> $hsides,Vector<bool> $vsides){
    	$this->grid   = $grid;
    	$this->hsides = $hsides;
    	$this->vsides = $vsides;

    	$this->answer = 'cuack_asnwer';
    	$this->name   = 'cuack_name';
    }
}
