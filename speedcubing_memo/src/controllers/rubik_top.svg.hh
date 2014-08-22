<?hh // partial
require $_SERVER['DOCUMENT_ROOT'] . '/config_speedcubing_memo.hh';

require APP_ROOT . '/src/models/RubikTopView.hh';

header("Content-type: image/svg+xml");

function str_to_vector6(string $str): Vector<bool>{
    $vc = Vector{};
    for($i=0;$i < strlen($str);$i++){
        $ch = $str[$i];
        $vc->add($ch === '1');
    }
    return $vc;
}
function str_to_matrix3x3(string $str): Matrix<bool>{
    return Vector{
        str_to_vector6(substr($str,0,3)),
        str_to_vector6(substr($str,3,3)),
        str_to_vector6(substr($str,6,3))
    };
}

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

        if($top->hsides[$i] === TRUE){
            $svg = $svg . draw_rectangle($x,$y,$square_size,$rect_size,'gray');
        }
    }
    for($i=0;$i<6;$i++){
        $x = $i < 3 ? 0 : $square_size * 3 + 15;
        $y = ($i % 3)*$square_size + 10;

        if($top->vsides[$i] === TRUE){
            $svg = $svg . draw_rectangle($x,$y,$rect_size,$square_size,'gray');
        }
    }

    return $svg;
}
function throw_bad_request(string $message):void{
    header('HTTP/1.1 400 Bad Request', true, 400);
    echo($message);
    exit();
}

$r_grid   = $_REQUEST['grid'];
$r_vsides = $_REQUEST['vsides'];
$r_hsides = $_REQUEST['hsides'];

if(is_null($r_grid) || strlen($r_grid) != 9 || substr_count($r_grid,'0') + substr_count($r_grid,'1') != 9){
    throw_bad_request("[grid] must be a string of size 9 made uniquely by ones and zeros");
}
if(is_null($r_vsides) || strlen($r_vsides) != 6 || substr_count($r_vsides,'0') + substr_count($r_vsides,'1') != 6){
    throw_bad_request("[vsides] must be a string of size 6 made uniquely by ones and zeros");
}
if(is_null($r_hsides) || strlen($r_hsides) != 6 || substr_count($r_hsides,'0') + substr_count($r_hsides,'1') != 6){
    throw_bad_request("[hsides] must be a string of size 6 made uniquely by ones and zeros");
}

$top = str_to_matrix3x3($r_grid);
$vsides = str_to_vector6($_REQUEST['vsides']);
$hsides = str_to_vector6($_REQUEST['hsides']);

echo '<svg width="200" height="200" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
    <g>';
echo draw_rubik_top(new RubikTopView($top,$hsides,$vsides,'none'));
echo '</g>
</svg>';
