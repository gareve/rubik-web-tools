<?hh // partial
require $_SERVER['DOCUMENT_ROOT'] . '/config_speedcubing_memo.hh';

require APP_ROOT . '/src/models/RubikTopView.hh';

header("Content-type: image/svg+xml");

function draw_rectangle(int $x, int $y, int $width, int $height, string $color) : string{
    return "<rect 
        style='fill:$color;stroke:#000000;stroke-opacity:1;fill-opacity:1'
        width='$width'
        height='$height'
        x='$x'
        y='$y' 
    />";
}

function draw_rubik_top(RubikTopView $top): string{
    $svg = '';
    $square_size = 50;
    $rect_size = 5;
    for($i=0;$i<3;$i++){
        $y = $i * $square_size + 10;
        for($j=0;$j<3;$j++){
            $x = $j * $square_size + 10;
            $value = $top->grid[$i][$j];

            $svg = $svg . draw_rectangle($x,$y,$square_size,$square_size,$value ? '#fffc00' : 'lightgray');
        }
    }
    for($i=0;$i<6;$i++){        
        $x = ($i % 3) * $square_size + 10;
        $y = $i < 3 ? 0 : $square_size * 3 + 15;

        if($top->vsides[$i] === TRUE){
            $svg = $svg . draw_rectangle($x,$y,$square_size,$rect_size,'gray');
        }
    }
    for($i=0;$i<6;$i++){
        $x = $i < 3 ? 0 : $square_size * 3 + 15;
        $y = ($i % 3)*$square_size + 10;

        if($top->hsides[$i] === TRUE){
            $svg = $svg . draw_rectangle($x,$y,$rect_size,$square_size,'gray');
        }
    }

    return $svg;
}
$top = Vector{
    Vector {true,false,true},
    Vector {false,false,true},
    Vector {true,false,false}
};
$hsides = Vector{true,false,true,false,true,false};
$vsides = Vector{true,false,true,false,true,false};

echo '<svg width="200" height="200" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
    <g>';
echo draw_rubik_top(new RubikTopView($top,$hsides,$vsides,'none'));
echo '</g>
</svg>';
