GaboFit = function()
{
  this.epsilon = 1;
}

GaboFit.prototype.fit = function(curve)
{
  if ( curve.length < 2 )
    return [{fit:"error"}];

  if ( curve.length == 2 || this.isLinear(curve) )
    return [{fit:"line", A:curve[0], B:curve[curve.length-1]}];

  var mostDist = this.linearMostDistant(curve);
//  console.log(mostDist + "/" + curve.length);
  var fitCircle = this.circleBy3([curve[0], curve[mostDist], curve[curve.length-1]]);
//  console.log(fitCircle);

  var rmse = this.Rmse(curve, fitCircle);
  // TODO: shouldn't be relative to circle dimension, use global epsilon!
  //  if ( rmse.e / fitCircle.R * 100 > 1 )
  if ( rmse.maxe > 0.5 )
  {
    // TODO: mostDist is not the best guess for dividing!
    mostDist = rmse.maxei;
    var subCurve1 = this.subArray(curve, 0, mostDist);
    var subCurve2 = this.subArray(curve, mostDist, curve.length-1);

    return this.fit(subCurve1).concat(this.fit(subCurve2));
  }
  return [{fit:"arc", A:curve[0], B:curve[curve.length-1], C:fitCircle}];
}

// Path cutter

GaboFit.prototype.findKeypoints = function(p)
{
  var val;
  var keypoints = [0];
  for (var i=1; i<p.length-1; i++)
  {
    var prev = p[i-1];
    var cur = p[i];
    var next = p[i+1];

    var angleFrom = Math.atan2(cur.Y - prev.Y, cur.X - prev.X) / Math.PI * 180;
    var angleTo = Math.atan2(next.Y - cur.Y, next.X - cur.X) / Math.PI * 180;
    var distFrom = this.distance(prev, cur);
    var distTo = this.distance(cur, next);

    var angleDiff = angleTo - angleFrom;
    if ( angleDiff < -180 ) 
      angleDiff += 360;
    if ( angleDiff > +180 ) 
      angleDiff -= 360;

    if ( i == 1 )
      val = angleDiff;

    // second derivation
    if ( Math.abs(val-angleDiff) > 2) // TODO: increase to 5, fix circle orientation!
    {
      keypoints.push(i);
      val = angleDiff;
    } else {
      // first derivation
      if ( Math.abs(angleDiff) > 20)
        keypoints.push(i);
    }
  }
  keypoints.push(p.length-1);
  return keypoints;
}

GaboFit.prototype.removeNear = function(p)
{
  var last = p[0], out = [last];
  for (var i=1; i<p.length; i++)  
  {
    var cur = p[i];
    if ( !this.isNear(last, cur) )
    {
      last = cur;
      out.push(cur);
    }
  }
  while (out.length > 1 && this.isNear(out[out.length-1], out[0]))
    out.pop();
  return out;
}

GaboFit.prototype.isNear = function(A, B)
{
  return Math.abs(A.X - B.X) < this.epsilon && Math.abs(A.Y - B.Y) < this.epsilon;
}

GaboFit.prototype.orientation = function(A, B, C)
{
  return (B.X - A.X) * (C.Y - A.Y) - (B.Y - A.Y) * (C.X - A.X) > 0;
}

// Tools
GaboFit.prototype.isLinear = function(curve)
{
  return this.leastSqrRegression(curve).r > 0.995;//999;
}

GaboFit.prototype.subArray = function(arr, from, to)
{
  var aux = [];
  for (var i=from; i<=to; i++)
    aux.push(arr[i]);
  return aux;
}

GaboFit.prototype.Rmse = function(curve, circle)
{
  var sum = 0;
  var mostdist = 0;
  var mostdisti = -1;
  var maxe = 0;
  var maxei = -1;
  for (var i=0; i<curve.length; i++)
  {
    var check;
//    if (Math.floor(i) == i)
      check = curve[i];
//    else
//      check = this.average(curve[Math.floor(i)%curve.length], curve[Math.floor(i+1)%curve.length]);

    var dist = this.distance(circle, check);
    if ( dist > mostdist )
    {
      mostdist = dist;
      mostdisti = Math.floor(i);
    }
    var err = Math.abs(dist - circle.R);
    sum += err*err;
    if (err > maxe)
    {
      maxe = err;
      maxei = Math.floor(i);
    }
  }
  sum /= curve.length;
  return {e:Math.sqrt(sum), i:mostdisti, maxe:maxe, maxei:maxei};
}

GaboFit.prototype.average = function(A, B)
{
  return {X:(A.X+B.X)/2, Y:(A.Y+B.Y)/2};
}

GaboFit.prototype.linearMostDistant = function(arr)
{
  var line = [arr[0], arr[arr.length-1]];
  var maxdist = 0, mostdistant = -1;
  for (var i=0; i<arr.length; i++)
  {
    var projection = this.projectToLine(arr[i], line);
    var dist = this.distance(projection, arr[i]);

    if ( dist > maxdist )
    {
      maxdist = dist;
      mostdistant = i;
    }
  }
  return mostdistant;
}

GaboFit.prototype.distance = function(A, B)
{
  return Math.sqrt( (B.X-A.X)*(B.X-A.X) + (B.Y-A.Y)*(B.Y-A.Y) );
}

GaboFit.prototype.projectToLine = function(p, l)
{
  var A = l[0];
  var B = l[1];
  var AB = {X:B.X-A.X, Y:B.Y-A.Y};
  var AB_sq = AB.X*AB.X + AB.Y*AB.Y;
  if ( AB_sq == 0 )
    return false;

  var Ap = {X:p.X-A.X, Y:p.Y-A.Y};
  var t = (Ap.X*AB.X + Ap.Y*AB.Y) / AB_sq;

  if (t < 0 || t > 1)
    return false;

  return {X:A.X + t*AB.X, Y:A.Y + t*AB.Y};   
}

// Approximations 

GaboFit.prototype.circleBy3 = function(p)
{
  var i;
  var r, m11, m12, m13, m14;
  var a = [[0, 0, 0], [0, 0, 0], [0, 0, 0]];

  for (i = 0; i < 3; i++) 
  {
    a[i][0] = p[i].X;
    a[i][1] = p[i].Y;
    a[i][2] = 1;
  }
  m11 = this.det( a, 3 );

  for (i = 0; i < 3; i++) 
  {
    a[i][0] = p[i].X*p[i].X + p[i].Y*p[i].Y;
    a[i][1] = p[i].Y;
    a[i][2] = 1;
  }
  m12 = this.det( a, 3 );

  for (i = 0; i < 3; i++) 
  {
    a[i][0] = p[i].X*p[i].X + p[i].Y*p[i].Y;
    a[i][1] = p[i].X;
    a[i][2] = 1;
  }
  m13 = this.det( a, 3 );

  for (i = 0; i < 3; i++) 
  {
    a[i][0] = p[i].X*p[i].X + p[i].Y*p[i].Y;
    a[i][1] = p[i].X;
    a[i][2] = p[i].Y;
  }
  m14 = this.det( a, 3 );

  if ( m11 == 0 )
    return false;

  var circle = {
    X :  0.5 * m12 / m11,
    Y : -0.5 * m13 / m11
  };

  circle.R = Math.sqrt( circle.X * circle.X + circle.Y * circle.Y + m14/m11 );
  return circle;
}

GaboFit.prototype.det = function(m)
{
  return m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) -
         m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
         m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}

GaboFit.prototype.leastSqrRegression = function(xyCollection)
{
   var SUMx = 0;     //sum of x values
   var SUMy = 0;     //sum of y values
   var SUMxy = 0;    //sum of x * y
   var SUMxx = 0;    //sum of x^2
   var SUMres = 0;   //sum of squared residue
   var res = 0;      //residue squared
   var slope = 0;    //slope of regression line
   var y_intercept = 0; //y intercept of regression line
   var SUM_Yres = 0; //sum of squared of the discrepancies
   var AVGy = 0;     //mean of y
   var AVGx = 0;     //mean of x
   var Yres = 0;     //squared of the discrepancies
   var Rsqr = 0;     //coefficient of determination
   var dataSize = xyCollection.length;

   //calculate various sums 
   for (var i = 0; i < dataSize; i++)
   {
      //sum of x
      SUMx = SUMx + xyCollection[i].X;
      //sum of y
      SUMy = SUMy + xyCollection[i].Y;
      //sum of squared x*y
      SUMxy = SUMxy + xyCollection[i].X * xyCollection[i].Y;
      //sum of squared x
      SUMxx = SUMxx + xyCollection[i].X * xyCollection[i].X;
   }

   //calculate the means of x and y
   AVGy = SUMy / dataSize;
   AVGx = SUMx / dataSize;

   //slope or a1
   slope = (dataSize * SUMxy - SUMx * SUMy) / (dataSize * SUMxx - SUMx*SUMx);

   //y itercept or a0
   y_intercept = AVGy - slope * AVGx;

   //calculate squared residues, their sum etc.
   for (var i = 0; i < dataSize; i++) 
   {
      //current (y_i - a0 - a1 * x_i)^2
      Yres = Math.pow((xyCollection[i].Y - y_intercept - (slope * xyCollection[i].X)), 2);

      //sum of (y_i - a0 - a1 * x_i)^2
      SUM_Yres += Yres;

      //current residue squared (y_i - AVGy)^2
      res = Math.pow(xyCollection[i].Y - AVGy, 2);

      //sum of squared residues
      SUMres += res;
   }

   //calculate r^2 coefficient of determination
   Rsqr = (SUMres - SUM_Yres) / SUMres;
   return {r:Math.sqrt(Rsqr)};
}
