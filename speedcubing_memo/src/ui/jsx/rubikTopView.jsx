/** @jsx React.DOM */
// The above declaration must remain intact at the top of the script.
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
  getInitialState : function(){
    return {data : {}};
  },
  componentDidMount: function(){
    $.ajax({
      url: this.props.url,
      dataType: 'json',
      success: function(data) {
        this.setState({data: data});
      }.bind(this),
      error: function(xhr, status, err) {
        console.error(this.props.url, status, err.toString());
      }.bind(this)
    });
  },
  render: function() {
    var rubikList = {};    
    for(var keyState in this.state.data){
      var rubikState = this.state.data[keyState];
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
  <RubikQuizTopList url='../top_view.json' />,
  document.getElementById('content')
);