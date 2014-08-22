/** @jsx React.DOM */
// The above declaration must remain intact at the top of the script.
var data = {
  "state_1":{"answer":"LRDE","grid":"010101010","hsides":"010101","vsides":"010101"},
  "state_2":{"answer":"LRDE","grid":"010101010","hsides":"010101","vsides":"010101"}
};

var RubikQuizTop = React.createClass({
  render: function() {
    var getRubikParams = 
      'grid='   + this.props.rubikState.grid   + '&' +
      'hsides=' + this.props.rubikState.hsides + '&' +
      'vsides=' + this.props.rubikState.vsides;

    return (
      <li>
        <h1>{this.props.rubikState.name}</h1>
        <img src={"../controllers/rubik_top.svg.hh?" + getRubikParams} /> <br />
        Answer : <span>{this.props.rubikState.answer}</span>
      </li>
    );  
  }
});
var RubikQuizTopList = React.createClass({
  render: function() {
    var rubikList = {};    
    for(var keyState in this.props.data){
      var rubikState = this.props.data[keyState];
      rubikList['state-' + keyState] = <RubikQuizTop rubikState={rubikState} />;
    }
    return (
      <ol>
        {rubikList}
      </ol>
    );  
  }
});
React.renderComponent(
  <RubikQuizTopList data={data}/>,
  document.getElementById('content')
);