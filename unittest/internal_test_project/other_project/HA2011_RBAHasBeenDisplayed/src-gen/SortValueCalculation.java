
import groovy.transform.CompileStatic;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.microsoft.z3.BoolExpr;
import com.microsoft.z3.Context;
import com.microsoft.z3.Expr;
import com.microsoft.z3.IntExpr;
import com.microsoft.z3.Solver;
import com.microsoft.z3.Status;

import rba.tool.core.z3.Z3CodeManager;

@CompileStatic
public class SortValueCalculation implements rba.tool.core.sort.ISortValueCalculation {

    Context ctx;
    IntExpr std;
    IntExpr min;
    IntExpr max;
    IntExpr non;

    BoolExpr stdConstr;
    BoolExpr minConstr;
    BoolExpr maxConstr;
    BoolExpr nonConstr;

    public void setUp() {
        ctx = new Context();
        std = ctx.mkIntConst("STANDARD");
        stdConstr = ctx.mkEq(std, ctx.mkInt(10));

        min = ctx.mkIntConst("MIN_VALUE");
        minConstr = ctx.mkEq(min, ctx.mkInt(0));

        max = ctx.mkIntConst("MAX_VALUE");
        maxConstr = ctx.mkEq(max, ctx.mkInt(9999));

        non = ctx.mkIntConst("NONE_VALUE");
        nonConstr = ctx.mkEq(non, ctx.mkInt(-1));
    }

    public void close() {
        ctx.close();
    }

    /**
     * Zorderの値を導出
     */
    public Map<String, Integer> calculateArea_zorder() {
        Solver s = ctx.mkSolver();
        s.push();

        List<Expr> areaList = new ArrayList<Expr>();
        List<BoolExpr> constrList = new ArrayList<BoolExpr>();
        List<BoolExpr> constrLabelList = new ArrayList<BoolExpr>();

        // エリア定義
        areaList.add(ctx.mkIntConst("A"));
        areaList.add(ctx.mkIntConst("X"));

        //A Zorder : STANDARD
        //X Zorder : STANDARD
        constrList.add(ctx.mkEq((IntExpr) areaList.get(0), std));
        constrList.add(ctx.mkEq((IntExpr) areaList.get(1), std));

        // 制約式のラベル付け
        constrLabelList.add(ctx.mkBoolConst("A"));
        constrLabelList.add(ctx.mkBoolConst("X"));

        s.add(stdConstr);
        s.add(minConstr);
        s.add(maxConstr);
        s.add(nonConstr);

        for (int i = 0; i < constrList.size(); i++) {
            s.assertAndTrack(constrList.get(i), constrLabelList.get(i));
        }

        Status st = s.check();
        Map<String, Integer> map = Z3CodeManager.INSTNACE.setModel(s, areaList, st);
        s.pop();
        return map;
    }

    /**
     * Visibilityの値を導出
     */
    public Map<String, Integer> calculateAllocatable_visibility() {
        Solver s = ctx.mkSolver();
        s.push();

        List<Expr> areaList = new ArrayList<Expr>();
        List<BoolExpr> constrList = new ArrayList<BoolExpr>();
        List<BoolExpr> constrLabelList = new ArrayList<BoolExpr>();

        // エリア定義
        areaList.add(ctx.mkIntConst("A"));
        areaList.add(ctx.mkIntConst("X"));

        //A Visibility : MAX
        //X Visibility : STANDARD
        constrList.add(ctx.mkEq((IntExpr) areaList.get(0), max));
        constrList.add(ctx.mkEq((IntExpr) areaList.get(1), std));

        // 視認性制約式のラベル付け
        constrLabelList.add(ctx.mkBoolConst("A"));
        constrLabelList.add(ctx.mkBoolConst("X"));

        s.add(stdConstr);
        s.add(minConstr);
        s.add(maxConstr);
        s.add(nonConstr);

        for (int i = 0; i < constrList.size(); i++) {
            s.assertAndTrack(constrList.get(i), constrLabelList.get(i));
        }

        Status st = s.check();
        Map<String, Integer> map = Z3CodeManager.INSTNACE.setModel(s, areaList, st);					

        s.pop();
        return map;
    }

    /**
     * priorityの値を導出
     */
    public Map<String, Integer> calculateContentState_priority() {
        Solver s = ctx.mkSolver();
        s.push();

        List<Expr> contentList = new ArrayList<Expr>();
        List<BoolExpr> constrList = new ArrayList<BoolExpr>();
        List<BoolExpr> constrLabelList = new ArrayList<BoolExpr>();

        // コンテンツ定義
        contentList.add(ctx.mkIntConst("A1_NORMAL"));
        contentList.add(ctx.mkIntConst("X1_NORMAL"));
        contentList.add(ctx.mkIntConst("X2_NORMAL"));
        contentList.add(ctx.mkIntConst("X3_NORMAL"));

        //A1_NORMALのpriority条件式[STANDARD]
        //X1_NORMALのpriority条件式[STANDARD]
        //X2_NORMALのpriority条件式[(STANDARD + 1)]
        //X3_NORMALのpriority条件式[(STANDARD + 2)]
        constrList.add(ctx.mkEq((IntExpr) contentList.get(0), std));
        constrList.add(ctx.mkEq((IntExpr) contentList.get(1), std));
        constrList.add(ctx.mkEq((IntExpr) contentList.get(2), ctx.mkAdd(std, (IntExpr) ctx.mkInt(1))));
        constrList.add(ctx.mkEq((IntExpr) contentList.get(3), ctx.mkAdd(std, (IntExpr) ctx.mkInt(2))));

        // 優先度制約式のラベル付け
        constrLabelList.add(ctx.mkBoolConst("A1_NORMAL"));
        constrLabelList.add(ctx.mkBoolConst("X1_NORMAL"));
        constrLabelList.add(ctx.mkBoolConst("X2_NORMAL"));
        constrLabelList.add(ctx.mkBoolConst("X3_NORMAL"));

        s.add(stdConstr);
        s.add(minConstr);
        s.add(maxConstr);
        s.add(nonConstr);

        for (int i = 0; i < constrList.size(); i++) {
            s.assertAndTrack(constrList.get(i), constrLabelList.get(i));
        }

        Status st = s.check();
        Map<String, Integer> map = Z3CodeManager.INSTNACE.setModel(s, contentList, st);
        s.pop();
        return map;
    }
}
