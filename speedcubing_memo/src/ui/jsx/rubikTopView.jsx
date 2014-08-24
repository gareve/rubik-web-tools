/** @jsx React.DOM */
// The above declaration must remain intact at the top of the script.
var RubikQuizTop = React.createClass({
  getInitialState : function(){
    return {randomKeys : [],rubikState:this.props.rubikState};
  },
  loadRandomRubikState:function(rubikTopStates){
    var randomKeys = this.state.randomKeys;
    if(randomKeys.length == 0){
      randomKeys = Object.keys(rubikTopStates);
      do{
        randomKeys.sort(function(){return .5 - Math.random();});//Not uniformly random
      }while(randomKeys.length > 1 && randomKeys[0] == this.state.lastKey);
    }
    var randomKey = randomKeys.shift();
    var rubikState = rubikTopStates[randomKey];

    this.setState({rubikState:rubikState,randomKeys:randomKeys,lastKey:randomKey});
  },
  isCorrectAnswer:function(clientAnswer){
    return clientAnswer == this.state.rubikState.answer;
  },
  toggleAnswerTF: function(){
    $(this.refs.answerSpan.getDOMNode()).toggle();
  },
  render: function() {
    if(this.state == null || this.state.rubikState == null){
      return <div></div>;
    }
    var getRubikParams = 
      'grid='   + this.state.rubikState.grid   + '&' +
      'hsides=' + this.state.rubikState.hsides + '&' +
      'vsides=' + this.state.rubikState.vsides;

    return (
      <div>
        <img src={"../controllers/rubik_top.svg.hh?" + getRubikParams} /> <br />
        Name : 
        <span ref='nameSpan'> {this.state.rubikState.name}</span><br />
        Answer : 
        <input type="checkbox" checked="true" ref="rubikAnswerCB" onChange={this.toggleAnswerTF}/>
        <span ref='answerSpan'>{this.state.rubikState.answer} </span>
        
      </div>
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
      <div>
        {rubikList}
      </div>
    );  
  }
});