package shuntingyard;

import java.util.Stack;

public class Modified_ShuntingYard_Evaluation {
	
	static String[] operators = {"^", "*", "/", "+", "-"};
	
	public static String convertToPostfix(String expression){
		
		String[] expArray = expression.split("");
		Stack<String> opStack = new Stack<String>();
		String outputString = "";
		
		for (String elem: expArray){
			
			if (isOperand(elem)) { 
				outputString += elem;
			}
			
			else {
				while((!opStack.isEmpty()) && (hasHigherPrecedence(opStack.peek(), elem))){
					outputString += opStack.pop();
				}
				
				opStack.push(elem);
			
			}
			
		}
		
		while (!opStack.isEmpty()){
			outputString += opStack.pop();
		}
		
		return outputString;
	}
	
	private static boolean isOperand(String token){
		
		for (String operator: operators){
			if (token.compareTo(operator) == 0){
				return false;
			}
		}
		
		return true;
	}
	
	private static boolean hasHigherPrecedence(String op1, String op2){
		return (getPrecedence(op1) >= getPrecedence(op2));
	}
	
	private static int getPrecedence(String operator)	{
		
		if (operator.compareTo("^") == 0){
			return 3;
		}
		
		else if ((operator.compareTo("*") == 0) || (operator.compareTo("/") == 0)){
			return 2;
		}
		
		else {
			return 1;
		}
		
	}
	
	public static double evaluatePostfix(String expression){
	
		
		String[] expArray = expression.split("");
		Stack<String> evalStack = new Stack<String>();
		double op1 = 0.0;
		double op2 = 0.0;
		double expValue = 0.0;
		
		
		for (String elem: expArray){
			
			if (isOperand(elem)){
				evalStack.push(elem);
			}
			
			else {
				op2 = Double.parseDouble(evalStack.pop());
				op1 = Double.parseDouble(evalStack.pop());
				
				evalStack.push(String.valueOf(performOperation(op1, op2, elem)));
			}
		}
		
		return Double.parseDouble(evalStack.pop());
		
	}
	
	private static double performOperation(double operand1, double operand2, String operator){
	
		if (operator.compareTo("^") == 0){
			return Math.pow(operand1, operand2);
		}
		
		else if (operator.compareTo("*") == 0) {
			return operand1*operand2;
		}
		
		else if (operator.compareTo("/") == 0){
			return operand1/operand2;
		}
		
		else if (operator.compareTo("+") == 0){
			return operand1+operand2;
		}
		
		else {
			return operand1-operand2;
		}
	}
	
	public static void main ( String [] args ) {
		String expression1 = "2+3*1" ;
		String expression2 = "2*3*4*5-8/2^3-9*2";
		//"3*2^4-7" ;
		String postfix1 = convertToPostfix ( expression1 ) ;
		String postfix2 = convertToPostfix ( expression2 ) ;
		System.out.println ( expression1 + "−>Postfix: " + postfix1 + " , Evaluation: "  + evaluatePostfix ( postfix1 ) ) ;
		System.out.println ( expression2 + "−>Postfix: " + postfix2 + " , Evaluation: "  + evaluatePostfix ( postfix2 ) ) ;
		}
	
	
}
