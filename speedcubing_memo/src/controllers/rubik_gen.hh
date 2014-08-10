<?hh // decl
require $_SERVER['DOCUMENT_ROOT'] . '/config_speedcubing_memo.hh';

require APP_ROOT . '/src/classes/RubikTopView.hh';

header("Content-type: image/svg+xml");

function draw_rubik_top(RubikTopView $top): string{    
    $svg = '';
    $square_size = 50;
    $rect_size = 5;
    for($i=0;$i<3;$i++){
        $y = $i * $square_size + 10;
        for($j=0;$j<3;$j++){
            $x = $j * $square_size + 10;
            $value = $top->grid[$i][$j];
            $color = $value ? '#fffc00' : 'lightgray';

            $svg = $svg . "<rect style='fill:$color;stroke:#000000;stroke-opacity:1;fill-opacity:1'
                       width='$square_size'
                       height='$square_size'
                       x='$x'
                       y='$y' />";
        }
    }

    for($i=0;$i<6;$i++){        
        $x = ($i % 3) * $square_size + 10;
        $y = $i < 3 ? 0 : $square_size * 3 + 15;
        $value = $top->vsides[$i];
        $color = 'gray';

        if($value === FALSE){
            continue;
        }
        $svg = $svg . "<rect style='fill:$color;stroke:#000000;stroke-opacity:1;fill-opacity:1'
                       width='$square_size'
                       height='$rect_size'
                       x='$x'
                       y='$y' />";
    }

    for($i=0;$i<6;$i++){
        $x = $i < 3 ? 0 : $square_size * 3 + 15;
        $y = ($i % 3)*$square_size + 10;
        $value = $top->hsides[$i];
        $color = 'gray';

        if($value === FALSE){
            continue;
        }

        $svg = $svg . "<rect style='fill:$color;stroke:#000000;stroke-opacity:1;fill-opacity:1'
                       width='$rect_size'
                       height='$square_size'
                       x='$x'
                       y='$y' />";
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