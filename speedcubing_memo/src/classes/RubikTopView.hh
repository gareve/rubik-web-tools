<?hh // decl
type Matrix<T> = Vector<Vector<T>>;

class RubikTopView{
    public function __construct(
        public Matrix<boolean> $grid,
        public Vector<boolean> $hsides,
        public Vector<boolean> $vsides,
        string $answer
    ){}
}